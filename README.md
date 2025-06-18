# [Tamatem Games ]

**Introduction:**
This project is an implementation of a side-scrolling game concept using Cocos2d-x. This application aims to meet the technical requirements for the Game Developer assignment provided.

**Implemented Features:**

* **Parallax Scrolling:** The parallax scrolling effect has been implemented, where background and foreground layers move at different speeds to create a sense of depth and distance during game movement.
* **Character Movement:** The main character of the game is displayed and is capable of horizontal movement (scrolling) and jumping.
* **Jump Button UI:** A dedicated "Jump" button is provided as part of the user interface to allow the player to control the character's jump action.
* **Mouse Scrolling:** Mouse scrolling support has been added, allowing the user to drag the screen horizontally with the left mouse button, providing an additional control experience for desktop environments.

**Development and Testing Environment:**
This project was fully developed and tested on **Windows OS** using **Microsoft Visual Studio 2022**.

**Important Note Regarding Android Build:**
The source code for this project is designed to be compatible with the Android platform. However, due to **storage space limitations on my development machine, I encountered challenges in installing and configuring all necessary components for the Android build environment (such as Android SDK, NDK, and JDK)**. These limitations prevented me from building and delivering a runnable Android APK file at this time.

I confirm that all requested functionalities and features have been implemented in the source code and are ready to be built and run on the Android platform once a properly configured development environment is available.

**How to Run the Project (on Windows):**

1.  **Clone this repository:**
    ```bash
    git clone https://github.com/osamadiab1/TamatemGames-cocos2dx
    ```
2.  **Open the project in Visual Studio:**
    * Navigate to the cloned project folder.
    * Open the `proj.win32\TamatemGames1.sln` file (e.g., `proj.win32\TamatemGames1.sln`) using Microsoft Visual Studio 2022.
3.  **Build and Run:**
    * In Visual Studio, ensure that "Solution Platform" is set to "Win32".
    * Go to the `Build` menu and select `Rebuild Solution`.
    * After the build process is complete, you can run the game by pressing the `Local Windows Debugger` (green arrow) or by going to the `Debug` menu and selecting `Start Debugging`.

**Source Code:**
The main source code for the game can be found in `Classes\HelloWorldScene.cpp`.



