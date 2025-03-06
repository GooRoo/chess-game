Create a local multiplayer chess game in Qt.

There should be 3 screens.

Once the application starts the **screen_1** appears. There should be at least the following elements on the screen:
- Start button – starts a new game. Leads to the **screen_2**
- Load button – allows user to load saved game. Leads to the **screen_3**
- Empty chess board

**Screen_2:**

Chess pieces are on the board (in initial position). User should be able to move the pieces with mouse according to the standard chess rules. Turn by turn rule must be followed as well (white turn-black turn- white-…). It’s not mandatory to implement the following: castling, check, checkmate. The following buttons should be accessible:
- Stop – application stops the game and leads to the screen_1
- Save – saves the game history to a file

**Screen_3:**

Loads a game history and allows to play it step by step using two buttons: “prev” and “next”. The following items are available on the screen:
- Start button – starts a new game. Leads to the screen_2
- Load button – allows user to load saved game. Leads to the screen_3
- Buttons “prev” and “next”
- chess board with pieces

**Evaluation criteria**: We will not care on graphics quality and comments in the code. But it is important that your application is stable, without any crashes and memory leaks. Also we will look into the application architecture, classes hierarchy, exceptions handling, coding practices

**Build system**: qmake

**Technologies**: Qt+QML is mandatory. C++11, boost – up to you

**Platform**: Windows or Linux
