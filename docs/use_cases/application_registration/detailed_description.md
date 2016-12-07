## Detailed description.
The expected result is the application registration on mobile device. SDL must registers application successfully. Flows for this event:   
SDL receives RegisterAppInterface RPC from mobile app or completely the same as in [PolicyTable](url) for the specified application.

After successful registration application should receive OnHMIStatus notification and OnPermissionChange notification.

The application is registered until it is terminated either by the application calling the UnregisterAppInterface method, or by SDL sending an OnAppInterfaceUnregistered notification, or by loss of the underlying transport connection, or closing of the underlying message transmission protocol RPC session.
Until the application receives its first OnHMIStatus Notification, its [HMI Status](url) is assumed to be: HMILevel=NONE, AudioStreamingState=NOT_AUDIBLE, SystemContext=MAIN. RegisterAppInterface must be processed before an application gets an HMILevel value.

In case last connection was unexpectedly closed, application
in case application was unexpected disconnect last time, resumption will be triggered.
Additional information available: [Resumption](url).
