This application provides information on how weather affects road maintenance and road conditions. For its operation, open-access data from the following official resources are used:

 
- https://en.ilmatieteenlaitos.fi/open-data

- https://www.digitraffic.fi/en/road-traffic/

- https://tie.digitraffic.fi/swagger/#/Maintenance

- https://tie.digitraffic.fi/swagger/#/Data%20v3/roadConditions

- https://tie.digitraffic.fi/swagger/#/Traffic%20message

 
# Running the project

## Prerequisits
* qt6-base, qt6-charts, and networkmanager-qt, qt5-base, qt6-compat.
* QT creator
* OS: the app was tested on Linux and Mac operating systems, but windows should also work properly.

## Compiling and running the project
1. open the App folder as a qt project in QT creator
2. click the play button on the bottom left to compile and run the app


# Features:
* display traffic data in combination with messages or weather
* save last user inputs and restore them
* save specific coordinates and give them a location name 
* export all graphs to PNG files
* store fetched data and restore it when needed
* visually compare fetched data with stored data 



# Using the app:

 You could look at the demo video provided with this project to get an idea how the app works as well as learn how to use it and see some example inputs.


### Available data

TrafficWeatherApp allows users to acquire open access data through the Digitraffic API and the FMI API and visualize how weather affects road conditions, required road maintenance, and traffic messages. Users must input the geodetic latitudes and longitudes of a square-shaped region boundary and select the time interval of interest. After the data is obtained, it is possible to visualize averages of different maintenance task types and weather conditions in the considered region. Other indices can be displayed, such as minimum, maximum, and average temperature values, cloudiness, and wind speed. In addition, past, current, and future weather status and road conditions in the given area can be displayed.

 

The application has two significant separate sections: 'Traffic Data' and 'Weather Data.' After starting the application, a user will be presented with a 'Traffic data' app window. App functionalities are explained in the lines to follow.

 
## Traffic Data

The Traffic data app window allows users to visualize 'Maintenance,' 'Road forecast,' 'Messages,' and compare to 'Weather data' from FMI API.

 
## Maintenance

Choosing 'Maintenance' allows for visualizing an overview of different maintenance task types. Users can input area coordinates, start time, end time, and maintenance task type. If the data for the selected task type exists, the graph with the maintenance count will appear, and the average of the selected task types will be displayed. The maintenance type name can be seen by hovering over the graph. Choosing a predefined location is possible from the dropdown menu, which automatically fills in the coordinate fields. Current inputs can be saved using the 'Save' option at the top of the window and choosing 'Maintenance inputs.' When choosing to restore 'Maintenance inputs,' the app automatically fills out the last saved user inputs. A specific location can be saved by choosing the 'Locations' tab at the top of the screen and selecting 'Add new predefined location.' This action opens a dialog, prompting the user to input the name of the location and geodetic coordinates of an area boundary. After clicking 'OK,' a new predefined location will appear in the predefined location's combo box. Every graph can be saved as a png image file, or the current data can be saved and loaded later for comparison to the data to be searched afterward. Button 'Clear_all' clears all the maintenance inputs and visualizations. The message and weather tab are on the right side of the window. By choosing the message tab, the user can display traffic messages for current locations, and the weather tab will display the current weather status in the given location and time.

 
## Road Forecast

The 'Road Forecast' tab can be chosen in Traffic Data to display road conditions in up to 12 hours. After entering area coordinates and time by clicking visualize, the forecast for 'Road temperature,' 'Wind direction,' 'Daylight,' 'Reliability,' 'Air temperature,' 'Wind speed,' 'Road condition,' 'Weather symbol,' and 'Forecast condition reason' can be seen. Line charts with current road and air temperature, wind speed, and wind direction will also be displayed. The current data can be saved, and previously saved data can be loaded. As in the maintenance part, current inputs can be saved, previously saved inputs can be loaded, and new predefined locations for the forecast can be added. Messages and current weather at the chosen location will be displayed on the right side of the screen.

 
## Messages

Traffic messages can be shown for up to the past 99 hours. Selectable options are 'TRAFFIC ANNOUNCEMENT,' 'EXEMPTED TRANSPORT,' 'WEIGHT RESTRICTION,' and 'ROAD WORK.' Current messages can be saved, and previously saved messages can be loaded and compared with current ones.

 
## Weather

The weather tab displays the line chart for weather for the current location and selected dates in either Maintenance or Road Forecast. The user can compare current data from the chosen tab to the weather status of selected dates and locations.

 
### Weather Data

Weather observations or weather forecasts can be visualized upon choosing the 'Weather Data' option. Required inputs are boundary latitudes and longitudes of a considered region, along with the start and end times. The following options to choose from are either 'Hourly observation,' 'Daily observation,' 'Monthly observation,' or 'Weather forecast.' By choosing one of the given Timestep options and choosing to visualize, the user will be able to see past, present or future temperature and wind speed. Cloudiness status is only available for weather observations, while temperature and wind are available for both. The weather page also has options for saving current user inputs, loading previously saved inputs, and adding new predefined locations. On the right side, the sidebar can visualize the maximum, minimum, and calculated averages of given data by clicking on CALCULATE button. The currently retrieved data can be saved, and previously saved data can be loaded.
