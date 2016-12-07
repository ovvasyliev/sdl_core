### Use Case 1. RegisterAppInterface - main flow (SUCCESS).

#### :one: **Main Flow - SUCCESS.**
In case RegisterAppInterface_request comes to SDL with correct structure and data and successfuly registered on SDL, SDL
1) notifies HMI with OnAppRegistered (Link) notification about application registering
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

#### :three: **Main flow - AppHMITypes is completely coincide with Policy data or not provided at all**
**_Preconditions:_** Local PT has several values in "AppHMIType" field in 'value-of-appID-the-app-has-registered-with' subsection of "app_policies" section.   
**_Steps:_** Application with appID is registering on SDL with several values of AppHMIType: all types exist in local PT or/ NO AppHMIType(s) in the request:
appID->SDL: RegisterAppInreface(params, appHMIType[])   
**_Expected:_** SDL registers the app and assigns all appHMIType(s) which are got from PT:
SDL->app: (resultCode: SUCCESS, success: true): RegisterAppInterface()



#### :six: **Main flow - AppHMITypes is completely coincide with Policy data or not provided at all.**
**_Preconditions:_** Local PT has several values in "AppHMIType" field in 'value-of-appID-the-app-has-registered-with' subsection of "app_policies" section.   
**_Steps:_** Application with appID is registering on SDL with several values of AppHMIType: all types exist in local PT or/ NO AppHMIType(s) in the request:
appID->SDL: RegisterAppInreface(params, appHMIType[]).   
**_Expected:_**
SDL registers the app and assigns all appHMIType(s) which are got from PT:
SDL->app: (resultCode: SUCCESS, success: true): RegisterAppInterface()

#### :seven: **Main flow - AppHMIType(s) are not included into an app's Policies.**
**_Precondition:_** Local PT does NOT have "AppHMIType" field in 'value-of-appID-the-app-has-registered-with' subsection of "app_policies" section
**_Steps:_** Application with appID is registering on SDL with at least one AppHMIType:
appID->SDL: RegisterAppInreface(params, appHMIType[])
**_Expected:_**
SDL registers the app and assigns the appHMITypes to the application which are got in the request:
SDL->app: (resultCode: SUCCESS, success: true): RegisterAppInterface()






Related Diagrams
Diagrams (for example activity diagram) describing this feature must be attached


2.1. Alternative flow for one of the steps above + expected SDL behavior in this flow
Describes alternative flow to Main flow described above.
Example: Main flow describes valid and allowed AddCommand
Alternative flow_1 -> app sends invalid request, for example
