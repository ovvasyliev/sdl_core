### Use Case 1. RegisterAppInterface - main flow (SUCCESS).

#### 1. **Main Flow - SUCCESS.**
In case RegisterAppInterface_request comes to SDL with correct structure and data and successfuly registered on SDL,   
SDL:   
1) notifies HMI with OnAppRegistered (Link) notification about application registering.   
2) responds with resultCode "SUCCESS" and success:"true" value to mobile application.

**_Preconditions:_**
Application with appID is registering on SDL.
Request data satisfies the conditions for successfull registration (for more details see RegisterAppInterface requirements).
Request structure satisfies mobile API restrictions (see RegisterAppInterface request structure).   
**_Steps:_** appID->RegisterAppInterface(params).   
_**Expected:**_   
1) SDL successfully registers application and notifies HMI:
SDL->HMI: OnAppRegistered(params)//parameters are defined in OnAppRegistered HMI API.   
2) Sending a response to mobile application:
SDL->appID: SUCCESS, success:"true":RegisterAppInterface().   
3) On registering the application, HMIStatus parameters are assinged to the application:
SDL->app: OnHMIStatus(hmiLevel,audioStreamingState, systemContext).   
4) SDL assigns the appropriate policies and notifies application:
SDL->app: OnPermissionsChange (params).

Related Diagrams
