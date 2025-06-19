from fastapi import FastAPI, HTTPException, status
from pydantic import BaseModel
from typing import Dict, List, Any
import sys
import os

build_dir = os.path.join(os.path.dirname(__file__), 'build')
if build_dir not in sys.path:
    sys.path.insert(0, build_dir)

import battleship_py  # pybind11-Modul, das die C++-Logik bereitstellt


# FastAPI-Anwendung initialisieren
app = FastAPI(
    title="Battleship REST API",
    description="REST-API für das Schiffeversenken-Spiel (Battleship) mit Mehrspieler- und Lobby-Support.",
    version="1.1.0"
)

# Globale Spiele-Instanzen
games: Dict[str, battleship_py.Game] = {}


class PlaceShipRequest(BaseModel):
    player_id: int
    ship_id: int
    pos1: List[int]  # [row, col] Startposition
    pos2: List[int]  # [row, col] Endposition

class MakeMoveRequest(BaseModel):
    player_id: int
    shot: List[int]  # [row, col]

def get_game_or_404(game_id: str) -> battleship_py.Game:
    """Hilfsfunktion: Gibt das Spiel zurück oder löst 404 aus."""
    game = games.get(game_id)
    if not game:
        raise HTTPException(status_code=status.HTTP_404_NOT_FOUND, detail="Game not found")
    return game

@app.post("/create_game/", status_code=201, description="Erstellt eine neue Spielinstanz mit eindeutiger ID.")
def create_game(game_id: str):
    """
    Erstellt ein neues Spiel mit der gegebenen ID.
    Parameter:
      - game_id: Eindeutige Spiel-ID (str)
    Rückgabe:
      - message: Bestätigungstext
      - game_id: Die erstellte Spiel-ID
    """
    if game_id in games:
        raise HTTPException(status_code=400, detail="Game ID already exists")
    games[game_id] = battleship_py.Game(int(game_id))
    return {"message": "Game created", "game_id": game_id}

@app.post("/join_game/", description="Tritt einem Spiel als Spieler oder Zuschauer bei.")
def join_game(game_id: str, player_id: int):
    """
    Spieler tritt einem Spiel bei. Die ersten beiden sind aktive Spieler, weitere ggf. Zuschauer.
    Parameter:
      - game_id: Spiel-ID (str)
      - player_id: Spieler-ID (int)
    Rückgabe:
      - joined: Gibt True/False zurück, ob das Joinen erfolgreich war
    """
    game = get_game_or_404(game_id)
    try:
        joined = game.join(player_id)
    except Exception as exc:
        raise HTTPException(status_code=400, detail=str(exc))
    return {"joined": joined}

@app.post("/start_game/", description="Startet das Spiel, wenn zwei Spieler beigetreten und Schiffe platziert wurden.")
def start_game(game_id: str):
    """
    Startet das Spiel, falls bereit.
    Parameter:
      - game_id: Spiel-ID (str)
    Rückgabe:
      - started: Gibt True/False zurück, ob das Spiel erfolgreich gestartet wurde
    """
    game = get_game_or_404(game_id)
    try:
        started = game.start_game()
        return {"started": started}
    except Exception as exc:
        raise HTTPException(status_code=400, detail=str(exc))

@app.post("/place_ship/", description="Platziert ein Schiff für einen Spieler.")
def place_ship(game_id: str, req: PlaceShipRequest):
    """
    Platziert ein Schiff auf dem Spielfeld eines Spielers.
    Parameter:
      - game_id: Spiel-ID (str)
      - req: PlaceShipRequest (player_id, ship_id, pos1, pos2)
    Rückgabe:
      - placed: Gibt True/False zurück, ob das Platzieren erfolgreich war
    """
    game = get_game_or_404(game_id)
    try:
        placed = game.place_ship(req.player_id, req.ship_id, tuple(req.pos1), tuple(req.pos2))
        return {"placed": placed}
    except Exception as exc:
        raise HTTPException(status_code=400, detail=str(exc))

@app.post("/make_move/", description="Führt einen Schuss eines Spielers aus.")
def make_move(game_id: str, req: MakeMoveRequest):
    """
    Führt einen Schuss eines Spielers aus.
    Parameter:
      - game_id: Spiel-ID (str)
      - req: MakeMoveRequest (player_id, shot)
    Rückgabe:
      - result: Ergebnis des Schusses
    """
    game = get_game_or_404(game_id)
    try:
        result = game.make_move(req.player_id, tuple(req.shot))
        return {"result": result}
    except Exception as exc:
        raise HTTPException(status_code=400, detail=str(exc))

@app.get("/game_state/", description="Gibt den aktuellen Spielstand zurück.")
def game_state(game_id: str):
    """
    Gibt den aktuellen Zustand des Spiels zurück.
    Parameter:
      - game_id: Spiel-ID (str)
    Rückgabe:
      - state: Aktueller Spielstand (z.B. als Dictionary oder String)
    """
    game = get_game_or_404(game_id)
    state = game.get_state()
    return {"state": state}

@app.get("/next_player/", description="Gibt die ID des Spielers zurück, der als nächstes am Zug ist.")
def next_player(game_id: str):
    """
    Gibt die ID des nächsten Spielers zurück.
    Parameter:
      - game_id: Spiel-ID (str)
    Rückgabe:
      - next_player: Spieler-ID (int)
    """
    game = get_game_or_404(game_id)
    player = game.get_next_player()
    return {"next_player": player}

@app.get("/lobby/", description="Listet alle laufenden Spiele und deren Teilnehmer.")
def lobby():
    """
    Gibt eine Liste aller Spiele und deren Teilnehmer zurück.
    Rückgabe:
      - Liste von Dictionaries mit game_id und players
    """
    return [
        {"game_id": gid, "players": list(game.get_participants())}
        for gid, game in games.items()
    ]