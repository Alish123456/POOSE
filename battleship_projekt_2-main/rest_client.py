import requests
import time

BASE_URL = "http://localhost:8000"

def create_game(game_id):
    r = requests.post(f"{BASE_URL}/create_game/", params={"game_id": str(game_id)})
    print("Create Game:", r.json())

def join_game(game_id, player_id):
    r = requests.post(f"{BASE_URL}/join_game/", params={"game_id": str(game_id), "player_id": player_id})
    print("Join Game:", r.json())

def place_ship(game_id, player_id, ship_id, pos1, pos2):
    data = {
        "player_id": player_id,
        "ship_id": ship_id,
        "pos1": pos1,
        "pos2": pos2
    }
    r = requests.post(f"{BASE_URL}/place_ship/", params={"game_id": str(game_id)}, json=data)
    print("Place Ship:", r.json())

def start_game(game_id):
    r = requests.post(f"{BASE_URL}/start_game/", params={"game_id": str(game_id)})
    print("Start Game:", r.json())

def make_move(game_id, player_id, shot):
    data = {
        "player_id": player_id,
        "shot": shot
    }
    r = requests.post(f"{BASE_URL}/make_move/", params={"game_id": str(game_id)}, json=data)
    print("Make Move:", r.json())

def poll_game_state(game_id, interval=2, times=5):
    print(f"Polling game {game_id} state every {interval}s ({times}x):")
    for _ in range(times):
        r = requests.get(f"{BASE_URL}/game_state/", params={"game_id": str(game_id)})
        print("Game State:", r.json())
        time.sleep(interval)

def show_lobby():
    r = requests.get(f"{BASE_URL}/lobby/")
    print("Lobby:", r.json())

if __name__ == "__main__":
    # Demo: Zwei Spieler, ein Spiel
    game_id = 1
    player1 = 101
    player2 = 202

    create_game(game_id)
    join_game(game_id, player1)
    join_game(game_id, player2)
    show_lobby()

    # Beispiel-Schiff platzieren (je nach Spiellogik ggf. anpassen)
    place_ship(game_id, player1, 1, [0,0], [0,4])
    place_ship(game_id, player2, 1, [1,0], [1,4])

    start_game(game_id)

    # Beispiel-Zug
    make_move(game_id, player1, [1,0])
    make_move(game_id, player2, [0,0])

    # Polling (Live-Update)
    poll_game_state(game_id)