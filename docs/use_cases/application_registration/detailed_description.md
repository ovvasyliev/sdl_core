## Detailed description.
The expected result is the application registration on mobile device. SDL must registers application successfully. Flows for this event:   
:white_small_square: SDL receives RegisterAppInterface RPC from mobile app or   
:white_small_square: completely the same as in [PolicyTable](url) for the specified application.

The order of requests/responses/notifications during application registering must be the following:   
1. app->SDL: RegisterAppInterface (policy_appID, parameters).   
2. SDL->HMI: OnAppRegistered (hmi_appID, params).   
3. SDL->app: RegisterAppInterface_response (`<applicable resultCode>`, success:true).   
4. SDL->app: OnHMIStatus(hmiLevel,audioStreamingState, systemContext).   
5. SDL->app: OnPermissionsChange(params).   
:information_source: Information:
`<applicable resultCode>` is the one that applies to successful registration:
WRONG_LANGUAGE
RESUME_FAILED
WARNINGS
SUCCESS
