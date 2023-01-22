
# AutoMute

AutoMute is a TeamSpeak 3 Addon.

AutoMute will let you choose, if you want to join servers muted. It will automaticly mute your mic and your speakers when you join a server.

## Prerequirements

To get this plugin to compile, you need the following Software:

- Visual Studio (2022 Version works fine, be sure to install wit C++ Desktop development)
- Qt 5.6.2 for 64 and 32 bit (https://download.qt.io/new_archive/qt/5.6/5.6.2/ - the third and the fourth .exe)

Note: Qt 5.6.2 has a bug that prevents the Qt Designer from running at all. To fix this, delete "Qt5WebEngineWidgets.dll" in the /bin folder of your Qt installation.

## Development

- Open the Project/Folder/Solution in Visual Studio and feel free to start coding.

- For changes to the GUI, just double click one of the .ui files inside the "Form Files" Folder. This will open up the Qt Designer where you can add, remove or edit Form elements.

- When building the solution, the appropriate .h files will be generated for the GUI files. Do not change these .h files inside "Generated Files" manually!

- When you are happy with your changes, go ahead and hit Build -> Build Solution in the top Navbar.

- You might need to play around with the build configuration at Build -> Configuration Manager. You want a Release configuration for both Win32 and x64.

- To test the Addon, move the built .dll file to the /config/plugins directory of your TeamSpeak 3 Client installation.

- When using printf inside your code, you might wonder how to see these printed logs. To see them, run the TeamSpeak 3 Client with the "-console" parameter. You can google how to do that.

## License
[MIT](https://choosealicense.com/licenses/mit/)