## Detailed description.
The expected result is the application registration on mobile device. SDL must registers application successfully. Flows for this event:   
SDL receives RegisterAppInterface RPC from mobile app or completely the same as in [PolicyTable](url) for the specified application.

After successful registration application should receive OnHMIStatus notification and OnPermissionChange notification.

The application is registered until it is terminated either by the application calling the UnregisterAppInterface method, or by SDL sending an OnAppInterfaceUnregistered notification, or by loss of the underlying transport connection, or closing of the underlying message transmission protocol RPC session.
Until the application receives its first OnHMIStatus Notification, its [HMI Status](url) is assumed to be: HMILevel=NONE, AudioStreamingState=NOT_AUDIBLE, SystemContext=MAIN. RegisterAppInterface must be processed before an application gets an HMILevel value.

In case last connection was unexpectedly closed, application
in case application was unexpected disconnect last time, resumption will be triggered.
Additional information available: [Resumption](url).

Application's VRsynonyms should NOT be checked for uniqueness through all other registered applications VRsynonyms.   
In case the app registers with the same "appName" as one of already registered "vrSynonyms" of other applications, SDL returns "resultCode: DUPLICATE_NAME, success: false" to such app.

SDL is case-insensetive when comparing the value of "appName" received within RegisterAppInterface against the value(s) of "nicknames" section for the corresponding appID provided by the application.   
SDL is case-insensetive when comparing the value of "appID" received within RegisterAppInterface against the value(s) of "app_policies" section.   
TTSName should not be checked for uniqueness against any of other parameters (within RegisterAppInterface or other registered applications). 

![Activity diagramm](http://www.plantuml.com/plantuml/proxy?src=https://raw.githubusercontent.com/LuxoftAKutsan/sdl_core/feature/application_registration_use_case/docs/use_cases/application_registration/assets/activity_diagramm.puml)
