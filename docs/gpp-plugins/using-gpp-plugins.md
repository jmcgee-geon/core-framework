# Customizing Resources per GPP

The GPP supports a plugin infrastructure that allows the addition of custom resource monitoring.
Plugins enable the extension of the GPP to monitor additional system attributes than those monitored by the GPP by default.
The following sections describe the operation of a GPP plugin and their development.

## Theory of operation

A plugin is a separate binary from GPP and is installed into `$SDRROOT/dev/devices/GPP/plugins`.
On startup, the GPP scans the directory `$SDRROOT/dev/devices/GPP/plugins` for any plugin binaries and launches each plugin with the following command line arguments:
  - instance id: identifier provided by GPP to use when passing messages
  - MessageConsumerPort reference: an IOR for a message port that consumes status messages from the plugin to the GPP

On plugin startup, the plugin registers with the GPP using the plugin's `message_out` port.

Plugins can manage any number of metrics.
Each metric is automatically registered when the plug sends a `plugin::message` to the GPP over the `message_out` port.
The `plugin::message` passes the result of its assessment of the metric it tracks.
The message contains the identifier for the plugin, the name of the metric, the measured metric, the threshold used, the reason why the metric triggered, a busy/not busy determination, and the timestamp for the decision.
If the plugin sets its message's busy flag to true, the GPP's usageState to BUSY.
If the plugin sets its message's busy flag to false, the flag has no effect on the GPP's usageState.
Metric thresholds can be changed by providing updates through the GPP's `plugin::update_metric` property.
The `plugin::update_metric` message is used to set the threshold for a specific metric on a specific plugin.

## Plugin Development

Plugins are generated using the `createGPPplugin` tool.

To create a new plugin, use the command-line tool with the plugin name as the argument:

    $ createGPPplugin pluginName

The tool creates a C++ project with autotools support and the following generated source files:
  - `pluginName.h` - The appropriate file to put header-related code in support of `pluginName.cpp`.

  - `pluginName.cpp` - The appropriate file for developers to add their own plugin behavior.

  - `main.cpp` - Housekeeping for the deployment of the plugin.

  - `struct_props.h` - Contains support classes for messaging between the plugin and the GPP. Modification of this file is not recommended.

  - `pluginName_base.h` - Support code for the plugin. Modification of this file is not recommended.

  - `pluginName_base.cpp` - Support code for the plugin. Modification of this file is not recommended.

After compiling and installing the plugin, it automatically becomes available the next time the GPP is deployed.

The plugin registers with the GPP on startup, giving the GPP a variety of registration information.
Items in the registration like the plugin description are updated by modifying the `registerPlugin` method in the file `pluginName.h`.

The `pluginName.cpp` file contains two methods that are designed to support the plugin functionality, `serviceFunction` and `updateThreshold`.

The `serviceFunction` function is the plugin's main thread function.
The processing thread is started automatically when the plugin launches.
This method is provided as a convenient place to include plugin processing, but the processing code can be placed anywhere in the plugin.
Exiting this function terminates the thread but does not affect the lifecycle of the plugin.

The plugin's `updateThreshold` method is invoked anytime a metric's threshold value is modified on the GPP.
This callback method exists to provide the user with the ability to modify the behavior of the plugin at runtime.
The received message structure contains three fields: the `plugin_id`, the `metric_name`, and the new `metric_threshold_value`.

## Plugin Messaging

The plugin's thresholds can be modified by changing GPP properties (described in the next section).
The plugin sends the GPP messages with metric updates.
To provide an update to the GPP from the plugin, create a `plugin_message_struct` instance and send it using the provided `message_out` port included in the plugin by the code generators.

The plugin message structure elements are:
<ul>
<li>busy (boolean): BUSY/not BUSY</li>
<li>plugin_id (string): The plugin's id (available in the _id plugin base class)</li>
<li>metric_name (string): Name for the metric. Must be unique in the plugin but does not have to be globally unique</li>
<li>metric_timestamp (CF::UTCTime): Timestamp for the message</li>
<li>metric_reason (string): Reason why the state is set (e.g.: value above threshold, value below threshold, value not equal to threshold)</li>
<li>metric_threshold_value (string): Trigger threshold for metric</li>
<li>metric_recorded_value (string): Recorded value</li>
</ul>

The metric and threshold in the message structure are defined as strings to simplify communications between the GPP and the plugin.
Part of the plugin development process is to convert the metric value to/from strings as appropriate.
The generated plugin code includes an example of sending a status message in the plugin's `serviceFunction` method.

## Run Time Plugin Inspection

Plugin status and their metric state/status can be inspected though the GPP properties `plugin::status` and `plugin::metric_status`, respectively.
Querying the GPP's `pluging::status` property provides the state of all the registered plugins.

The `plugin::status` is a sequence of structures whose elements are:
<ul>
<li>id (string): The plugin's id</li>
<li>name (string): The plugin's name</li>
<li>description (string): The plugin's description</li>
<li>busy (boolean): BUSY/not BUSY</li>
<li>alive (boolean): Plugin process is alive/not alive</li>
<li>pid (CORBA::Ulong): The plugin's process id</li>
<li>metric_names (string sequence): List of metrics the plugin is evaluating</li>
</ul>

The `plugin::metric_status` structure provides detailed information about the metrics monitored by the different plugins.
While the `plugin::status` property provides an overview of the different plugins, `plugin::metric_status` provides insight into each of the metrics monitored by any running plugins.
The `plugin::metric_status` is a sequence of structures whose elements are:
<ul>
<li>plugin_id (string): The plugin's id (available in the _id plugin base class)</li>
<li>metric_name (string): Name for the metric. Must be unique in the plugin but does not have to be globally unique</li>
<li>busy (boolean): BUSY/not BUSY</li>
<li>metric_timestamp (CF::UTCTime): Timestamp for the last message received by the GPP from this metric</li>
<li>metric_reason (string): Most recent reason why the state was set (e.g.: value above threshold, value below threshold, value not equal to threshold)</li>
<li>metric_threshold_value (string): Current trigger threshold for metric</li>
<li>metric_recorded_value (string): Most recent recorded value</li>
</ul>

## Run Time Metric Control
Control is performed through the GPP's `plugin::update_metric` property.
Each plugin can manage multiple metrics, so messages regarding changes in a threshold value need to be addressed with the plugin id and the metric in question.

The `plugin::update_metric` message structure elements are:
<ul>
<li>plugin_id (string): The plugin's id</li>
<li>metric_name (string): The metric's name</li>
<li>metric_threshold_value (string): The new threshold value for the metric</li>
</ul>

The generated plugin code includes the callback function to respond to a `plugin::update_metric` message.