# API reference

# Endpoints
## Players
| Method      | Endpoint              | Description                                     | Parameters           | Response                  |
|-------------|-----------------------|-------------------------------------------------|----------------------|---------------------------|
| GET         | `/api/player`         | [Get all users](#fetch-all-players)             | None                 | JSON list of players      |
| GET         | `/api/player/{id}`    | [Get a player by ID](#fetch-player-by-id)       | `id`: int            | JSON player object        |
| POST        | `/api/player`         | [Create a new user](#create-new-player)         | JSON body            | Created player object     |
| PATCH       | `/api/player/{id}`    | [Update a user by ID](#update-player)           | `id`: int, JSON body | Updated player object     |
| DELETE      | `/api/player/{id}`    | [Delete a user by ID](#delete-player)           | `id`: int            | Status message            |

## Score

# Endpoints explained

## Fetch all players 

**URL** : `/api/player`

**Method** : `GET`


### Success Response

**Code** : `200 OK`

**Response examples**

```json
{
    "id": 1,
    "name": "John Doe",
},
{
    "id": 2,
    "name": "John Doe 2nd",
}
```

## Fetch player by id

Get the details of the currently Authenticated User along with basic
subscription information.

**URL** : `/api/player/{id}`

**Method** : `GET`


### Success Response

**Code** : `200 OK`

**Response examples**

```json
{
    "id": 1,
    "name": "John Doe",
}
```

## Create new player

Create a new player by providing a name parameter in the query.

**URL** : `/api/player?name=John Doe`

**Method** : `POST`

**Parameters**: `{name: {name}}`

### Success Response

**Code** : `200 OK`

**Response examples**

```json
{
    "message": "Player created",
    "id": "1"
}
```

**No name provided**

**Code** : `422 Unprocessable Entity`
```json
{"errors":["Name is required"]}
```

## Update player

**URL** : `/api/player?name=John Doe`

**Method** : `POST`

**Parameters**: `{name: {name}}`

### Success Response

**Code** : `200 OK`

**Response examples**

```json
{
    "message":"Player updated",
    "rows":"1"
}
```

## Delete player

**URL** : `/api/player/{id}`

**Method** : `POST`

### Success Response

**Code** : `200 OK`

**Response examples**

```json
{
    "message":"Player deleted",
    "rows":"1"
}
```

