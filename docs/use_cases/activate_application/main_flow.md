### Use Case 1. SDL must allow to activate app from any HMILevel - main flow

_**Preconditions:**_  
Application HMI Type: any  
appID successfully registers on SDL _see_ [Application Registration] (https://github.com/LuxoftAKutsan/sdl_core/blob/feature/application_registration_use_case/docs/use_cases/application_registration/detailed_description.md)  
appID in other-than-NULL policies  
_**Steps:**_  
HMI -> SDL: SDL.ActivateApp (appID)  
_**Expected:**_  
SDL -> HMI: SDL.ActivateApp (SUCCESS)  
SDL -> appID: OnHMIStatus maximum possible HMILevel

**Related Diagram**

App activation

![App activation](http://www.plantuml.com/plantuml/proxy?src=https://raw.githubusercontent.com/LuxoftAKutsan/sdl_core/feature/activate_application_use_case_requirements/docs/use_cases/activate_application/assets/activate_app_main_flow.puml)  
