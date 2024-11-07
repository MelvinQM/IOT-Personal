# Database

## Contents
- **[1. Database Overview](#1-database-overview)**
   - **[1.1 Entity-Relationship Diagram (ERD)](#11-entity-relationship-diagram-erd)**
   - **[1.2 EER Diagram](#12-eer-diagram)**
- **[2. Database Setup](#2-database-setup)**
   - **[2.1 MySQL Workbench](#21-mysql-workbench)**
- **[3. Database Design](#3-database-design)**
   - **[3.1 Tables](#31-tables)**
     - **[3.1.1 Player Table](#311-player-table)**
     - **[3.1.2 Score Table](#312-score-table)**
     - **[3.1.3 Session Table](#313-session-table)**
     - **[3.1.4 Difficulty Table](#314-difficulty-table)**
   - **[3.2 Relationships](#32-relationships)**

## 1. Database overview
### 1.1 Entity-Relationship Diagram Diagram (ERD)
Below the ERD is shown. This concept allows the system to be able to store player data through sessions. A session is the time a single player is playing with the game console. A session can contain more than one score. A player can also have more than one session if the same username is used to start a new session this session will be linked to the same player id.

<div align="center">
  <img src="/../assets/images/ERD2.drawio.png" alt="ERD">
</div>

The player starts the embedded device then is prompted with a session id. The player then goes to the website and fills in their name and session id. This creates the player if the name didnt already exist and binds the session to this player. The device is polling until a player is added to the current session. Only then can the game start

### 1.2 EER Diagram
To realise the previous established ERD this EER diagram was generated from the made tables this shows the different types of data that will be stored and the relation between the tables.
<div align="center">
  <img src="/../assets/images/EER.png" alt="EER">
</div>

## 2. Database setup
### 2.1 MYSQLWorkbench
To interface with the SQL Database MYSQLWorkbench was used. To connect to the database through this program you need to fill in the sql login details.
<div align="center">
  <img src="/../assets/images/sqlworkbenchconnect.png" alt="sqlworkbench">
</div>

### 2.2 Initializing database
- Copy the sql script from [databaseInit.sql.](https://gitlab.fdmci.hva.nl/IoT/2024-2025-semester-1/individual-project/nuufoowaamee68/-/blob/main/web/database/databaseInit.sql?ref_type=heads)
- Make a new query to an empty database (this can be done through MYSQLWorkbench).
- Paste the script and edit "databasename" to your database name.
- Run the script.

## 3.1 Database Design
### 3.1 Tables
#### 3.1.1 Player table
The player table consists of 2 columns:

- *ID*: the identifier
- name: the players name (Unique)

<img src="/../assets/images/player-table.png" alt="player-table">

#### 3.1.2 Score table
The score table consists of 3 columns:

- *ID*: the identifier.
- session_id: the id of the session the score occured in.
- score: used to store the score count.

<img src="/../assets/images/score-table.png" alt="score-table">

#### 3.1.3 Session table
The session table consists of 6 columns:

- *ID*: the identifier.
- completed: if the session has ended.
- start_time: the start time of the session.
- end_time: the end time of the session.
- player_id: the id of the player which started the session.
- difficulty_id: indicates the selected difficulty of the session.

<img src="/../assets/images/session-table.png" alt="session-table">



#### 3.1.4 Difficulty table
The difficulty table consists of 2 columns:

- *ID*: the identifier.
- name: the name of the difficulty.

<img src="/../assets/images/difficulty-table.png" alt="difficulty-table">


### 3.2 Relationships
Between the mentioned tables some relationships are of note:

- A difficulty can be used in multiple sessions.
- A session can only have one difficulty.
- Player can have multiple sessions.
- A session can only have one player.
- A session can have multiple scores.
- A score can only have one session.


