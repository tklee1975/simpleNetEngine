# Design Note 

## SimpleNetApp 

### Key Class 
- SimpleNetApp -- (extends) -> BaseImguiApp 
               -- (has) --> SNHost  
               -- (use) --> SimpleNetAppSessionFactory 
                            - (create) -> SimpleHostSession
                            - (create) -> SimpleClientSession 

  This class is the main entry to run the Demo Net App (using IMGUI);
  It intend to be a host or a client. 

- BaseImguiApp
  This class is a base class for different ImguiApp. 
  

- SNHost 
  A common class to handle "host" logic. The main logic is controlled by SNSession.

- SimpleNetAppSessionFactory
  - The factory to create SimpleHostSession & SimpleClientSession 

- SimpleHostSession
  - The logic to handle host session 

- SimpleClientSession (not yet created)
  - The logic to handle client session 

