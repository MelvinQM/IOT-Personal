# API reference

## Contents
- **[1. API Structure](#1-api-structure)**
- **[2. Player Endpoints](#2-player-endpoints)**
- **[3. Score Endpoints](#3-score-endpoints)**
- **[4. Session Endpoints](#4-session-endpoints)**
- **[5. Difficulty Endpoints](#5-difficulty-endpoints)**
- **[6. Actions Endpoints](#6-actions-endpoints)**

## 1. API Structure
The api is designed to allow CRUD operations with the tables of the the connected database. To see more information on all the tables and their collumns see the [Database](/web/database) page. The only exception to this is the Actions endpoint which provides helper functions such as `getHighscores` which interfaces with both the player and score tables.

## 2. Player Endpoints
See [Player](/web/database#311-player-table) table.

| Method  | Endpoint            | Description                                  | Response (JSON)        |
|---------|---------------------|----------------------------------------------|------------------------|
| GET     | `/api/player`       | [Fetch all players](#21-fetch-all-players)   | List of players        |
| GET     | `/api/player/{id}`  | [Fetch player by ID](#22-fetch-player-by-id) | Player object          |
| POST    | `/api/player`       | [Create new player](#23-create-new-player)   | Created player id      |
| PATCH   | `/api/player/{id}`  | [Update player by ID](#24-update-player)     | Affected rows          |
| DELETE  | `/api/player/{id}`  | [Delete player by ID](#25-delete-player)     | Affected rows          |


<br>

### 2.1 Fetch all players
---
**URL** :  **`/api/player`**

**Filter Query**: Option to use parameter name to specify only the player with that name *(names are unique)* `ex: /api/player?name={name}`

**Method** : **`GET`**

**Response**:

*Code* : `200 OK`

```json
[
    {
        "id": 1,
        "name": "John Doe",
    },
    {
        "id": 2,
        "name": "John Doe 2nd",
    }
]
```

<br>

### 2.2 Fetch player by id
---
**URL** : **`/api/player/{id}`**

**Method** : **`GET`**


**Response**:

*Code* : `200 OK`

```json
{
    "id": 1,
    "name": "John Doe"
}
```

<br>

### 2.3 Create new player
---

**URL** : **`/api/player`**

**Method** : **`POST`**

**Body Params**:

| Parameter | Type   | Required |Description                      |
|-----------|--------|----------|---------------------------------|
| name	    | string | Yes	    |Name of the new player           |

*Body Example*:
```json
{
    "name": "John Doe"
}
```

**Response**:

*Code* : `200 OK`

```json
{
    "message": "Player created",
    "id":  1
}
```

<br>

### 2.4 Update player
---
**URL** : **`/api/player/{id}`**

**Method** : **`PATCH`**

**Body**: 

| Parameter | Type   | Required |Description                      |
|-----------|--------|----------|---------------------------------|
| name	    | string | Yes	    | New name for player             |

*Body Example*:
```json
{
    "name": "John Doe"
}
```

**Response**:

*Code* : `200 OK`
```json
{
    "message":"Player updated",
    "rows": 1
}
```
<br>

### 2.5 Delete player
---
**URL** : **`/api/player/{id}`**

**Method** : **`DELETE`**

**Response**:

*Code* : `200 OK`
```json
{
    "message":"Player deleted",
    "rows": 1
}
```

<br>

## 3. Score Endpoints
See [Score](/web/database#312-score-table) table.

| Method  | Endpoint            | Description                                   | Response (JSON)        |
|---------|---------------------|-----------------------------------------------|------------------------|
| GET     | `/api/score`        | [Fetch all scores](#31-fetch-all-scores)      | List of scores         |
| GET     | `/api/score/{id}`   | [Fetch score by ID](#32-fetch-score-by-id)    | Score object           |
| POST    | `/api/score`        | [Create new score](#33-create-new-score)      | Created score id       |
| PATCH   | `/api/score/{id}`   | [Update score by ID](#34-update-score)        | Affected rows          |
| DELETE  | `/api/score/{id}`   | [Delete score by ID](#35-delete-score)        | Affected rows          |


<br>

### 3.1 Fetch all scores
---
**URL** :  **`/api/score`**

**Method** : **`GET`**

**Response**:

*Code* : `200 OK`

```json
[
    {
        "id":1,
        "session_id":1,
        "score":100
    },
    {
        "id":2,
        "session_id":2,
        "score":200
    }
]
```

<br>

### 3.2 Fetch score by id
---
**URL** : **`/api/score/{id}`**

**Method** : **`GET`**


**Response**:

*Code* : `200 OK`

```json
{
    "id":1,
    "session_id":1,
    "score":100
}
```

<br>

### 3.3 Create new score
---

**URL** : **`/api/score`**

**Method** : **`POST`**

**Body**: 

| Parameter    | Type   | Required  | Description                            |
|--------------|--------|-----------|----------------------------------------|
| score	       | int    | Yes	    | Score amount from game                 |
| session_id   | int    | Yes	    | Id of session where score was achieved |

*Body Example*:
```json
{
    "session_id": 1,
    "score": 100
}
```

**Response**:

*Code* : `200 OK`

```json
{
    "message": "Score created",
    "id": 1
}
```

<br>

### 3.4 Update score
---
**URL** : **`/api/score/{id}`**

**Method** : **`PATCH`**

**Body**: 

| Parameter    | Type   | Required  | Description                            |
|--------------|--------|-----------|----------------------------------------|
| score	       | int    | Yes	    | New score amount                       |

*Body Example*:
```json
{
    "score": 100
}
```


**Response**:

*Code* : `200 OK`
```json
{
    "message":"Score updated",
    "rows": 1
}
```
<br>

### 3.5 Delete score
---
**URL** : **`/api/score/{id}`**

**Method** : **`DELETE`**

**Response**:

*Code* : `200 OK`
```json
{
    "message":"Score deleted",
    "rows": 1
}
```


<br>

## 4. Session Endpoints
See [Session](/web/database#313-session-table) table.

| Method  | Endpoint            | Description                                    | Response (JSON)        |
|---------|---------------------|------------------------------------------------|------------------------|
| GET     | `/api/session`      | [Fetch all sessions](#41-fetch-all-sessions)   | List of sessions       |
| GET     | `/api/session/{id}` | [Fetch session by ID](#42-fetch-session-by-id) | Session object         |
| POST    | `/api/session`      | [Create new session](#43-create-new-session)   | Created session id     |
| PATCH   | `/api/session/{id}` | [Update session by ID](#44-update-session)     | Affected rows          |
| DELETE  | `/api/session/{id}` | [Delete session by ID](#45-delete-session)     | Affected rows          |


<br>

### 4.1 Fetch all sessions
---
**URL** :  **`/api/session`**

**Method** : **`GET`**

**Response**:

*Code* : `200 OK`

```json
[
    {
        "session_id": 1,
        "player_id": 1,
        "difficulty_id": 1,
        "completed": true,
        "use_gyro": true,
        "start_time": "0000-00-00 00:00:00",
        "end_time": "0000-00-00 00:00:00"
    }
    {
        "session_id": 2,
        "player_id": 1,
        "difficulty_id": 1,
        "completed": true,
        "use_gyro": true,
        "start_time": "0000-00-00 00:00:00",
        "end_time": "0000-00-00 00:00:00"
    }
]
```

<br>

### 4.2 Fetch session by id
---
**URL** : **`/api/session/{id}`**

**Method** : **`GET`**

**Response**:

*Code* : `200 OK`

```json
{
    "session_id": 1,
    "player_id": 1,
    "difficulty_id": 1,
    "completed": true,
    "use_gyro": true,
    "start_time": "0000-00-00 00:00:00",
    "end_time": "0000-00-00 00:00:00"
}
```

<br>

### 4.3 Create new session
---

**URL** : **`/api/session`**

**Method** : **`POST`**

**Body**: 

| Parameter         | Type      | Required  | Description                                                           |
|-------------------|-----------|-----------|-----------------------------------------------------------------------|
| player_id	        | int       | No	    | Id of player that is connected to session                             |
| difficulty_id     | int       | No	    | Id of the selected difficulty                                         |
| completed         | bool      | No	    | Boolean storing if the session has been ended                         |
| use_gyro          | bool      | No	    | Boolean storing whether the game is using gyro controls or joystick   |
| start_time        | DateTime  | No	    | The start time of the session                                         |
| end_time          | DateTime  | No	    | The end time of the session                                           |

*Body Example*:
```json
{
    "player_id": 1,
    "difficulty_id": 1,
    "completed": true,
    "use_gyro": true,
    "start_time": "0000-00-00 00:00:00",
    "end_time": "0000-00-00 00:00:00"
}
```

*Note*: All fields in body can be omitted to create session with no defined settings as these could be added later.

**Response**:

*Code* : `200 OK`

```json
{
    "message": "Session created",
    "id":  1
}
```

<br>

### 4.4 Update session
---
**URL** : **`/api/session/{id}`**

**Method** : **`PATCH`**

**Body**: 

| Parameter         | Type      | Required  | Description                                                           |
|-------------------|-----------|-----------|-----------------------------------------------------------------------|
| player_id	        | int       | No	    | Id of player that is connected to session                             |
| difficulty_id     | int       | No	    | Id of the selected difficulty                                         |
| completed         | bool      | No	    | Boolean storing if the session has been ended                         |
| use_gyro          | bool      | No	    | Boolean storing whether the game is using gyro controls or joystick   |
| start_time        | DateTime  | No	    | The start time of the session                                         |
| end_time          | DateTime  | No	    | The end time of the session                                           |

*Body Example*:
```json
{
    "player_id": 1,
    "difficulty_id": 1,
    "completed": true,
    "use_gyro": true,
    "start_time": "0000-00-00 00:00:00",
    "end_time": "0000-00-00 00:00:00"
}
```
*Note*: All fields in body can be changed or left the same by ommitting them from the body. Additionally once a session is completed (completed == true) changes can no longer be applied through this method.

**Response**:

*Code* : `200 OK`
```json
{
    "message":"Session updated",
    "rows": 1
}
```
<br>

### 4.5 Delete session
---
**URL** : **`/api/session/{id}`**

**Method** : **`DELETE`**

**Response**:

*Code* : `200 OK`
```json
{
    "message":"Session deleted",
    "rows": 1
}
```

<br>

## 5. Difficulty Endpoints
See [Difficulty](/web/database#314-difficulty-table) table.

| Method  | Endpoint                | Description                                           | Response (JSON)        |
|---------|-------------------------|-------------------------------------------------------|------------------------|
| GET     | `/api/difficulty`       | [Fetch all difficulties](#51-fetch-all-difficulties)  | List of difficulties   |
| GET     | `/api/difficulty/{id}`  | [Fetch difficulty by ID](#52-fetch-difficulty-by-id)  | Difficulty object      |

<br>

### 5.1 Fetch all difficulties
---
**URL** :  **`/api/difficulty`**

**Method** : **`GET`**

**Response**:

*Code* : `200 OK`

```json
[
  {
    "id": 1,
    "name": "Easy"
  },
  {
    "id": 2,
    "name": "Normal"
  },
  {
    "id": 3,
    "name": "Hard"
  }
]
```

<br>

### 5.2 Fetch difficulty by id
---
**URL** : **`/api/difficulty/{id}`**

**Method** : **`GET`**

**Response**:

*Code* : `200 OK`

```json
{
"id": 1,
"name": "Easy"
}
```

<br>

## 6. Actions Endpoints
The actions endpoints are not based on one single table. These are more like helper functions.

| Method  | Endpoint                       | Description                                           | Response (JSON)        |
|---------|--------------------------------|-------------------------------------------------------|------------------------|
| GET     | `/api/actions/gethighscores`   | [Fetch highscores](#61-fetch-highscores)              | List of highscores     |

<br>

### 6.1 Fetch highscores
---
**URL** :  **`/api/actions/gethighscores`**

**Filter Query**: Option to use parameter count to specify the amount of highscores `ex: api/actions/gethighscores?count=10`

**Method** : **`GET`**

**Response**:

*Code* : `200 OK`

```json
[
  {
    "score": 1001,
    "name": "John Doe"
  },
  {
    "score": 1000,
    "name": "Jane Doe"
  }
]
```

<br>
