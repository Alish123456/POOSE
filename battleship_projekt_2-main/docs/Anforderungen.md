# Checkliste / Aufgabenstellung: Mehrspieler-Spielserver (Phase 2)

Diese Checkliste dient als Leitfaden, um alle Anforderungen der Aufgabenstellung systematisch zu erfüllen und das Projekt nachvollziehbar, funktionsfähig und dokumentiert abzugeben.

---

## 1. Spiel-Logik entwickeln (C++)

- [ ] Entscheide dich für ein geeignetes Mehrspieler-Spiel (z. B. Hangman, Blackjack, Mau Mau).
- [ ] Implementiere die gesamte Spiellogik in C++:
  - [ ] Verwaltung von Spielern und deren Zuständen.
  - [ ] Spielfluss (Runden, Züge, Siegbedingungen, etc.).
  - [ ] Spielfeld, Karten, Wörter oder andere relevante Datenstrukturen.
  - [ ] Unterstützung für mehrere gleichzeitige Spielinstanzen.
- [ ] Schreibe Unit-Tests für die Spiellogik (optional, aber empfohlen).

---

## 2. C++-Python-Anbindung mit pybind11

- [ ] Baue ein Python-Modul aus der Spiellogik mittels pybind11.
- [ ] Stelle sicher, dass alle Spielfunktionen sowie der Spielzustand von Python aus aufrufbar bzw. einsehbar sind.
- [ ] Dokumentiere die Schnittstelle (Klassen, Methoden, Rückgabewerte).

---

## 3. REST-Server mit FastAPI & uvicorn

- [ ] Erstelle einen REST-Server in Python mit FastAPI.
- [ ] Binde das pybind11-Modul im REST-Server ein (Import & Nutzung).
- [ ] Definiere alle nötigen REST-Endpunkte für das Spiel:
  - [ ] Spiel erstellen
  - [ ] Spiel beitreten
  - [ ] Lobby anzeigen
  - [ ] Spiel starten
  - [ ] Spielzug ausführen
  - [ ] Spielzustand abfragen (für Polling)
  - [ ] (ggf. weitere, z. B. „Spiel verlassen“)
- [ ] Dokumentiere alle Endpunkte (Pfad, Methode, Parameter, Rückgabe) mit Docstrings und/oder FastAPI-Beschreibung.
- [ ] Starte den Server mit uvicorn und stelle sicher, dass der Import des C++-Moduls klappt (z. B. via PYTHONPATH oder sys.path).

---

## 4. Lobby- und Spielinstanz-Management

- [ ] Implementiere eine Lobby, in der sich Spieler vor Spielstart aufhalten können.
- [ ] Ermögliche das Erstellen und Verwalten von mehreren parallelen Spielinstanzen.
- [ ] Spiele und Spieler müssen eindeutig identifizierbar sein (z. B. IDs).
- [ ] Dokumentiere die Datenmodelle (Lobby, Spieler, Spielinstanz).

---

## 5. REST-Client

- [ ] Implementiere einen REST-Client (z. B. in Python, mit „requests“).
- [ ] Simuliere mehrere Spieler (mind. zwei), die die Endpunkte nutzen.
- [ ] Implementiere Live-Updates des Spielzustands (z. B. Polling im Sekundentakt).
- [ ] Gib alle relevanten Server-Antworten und Statusmeldungen in der Konsole aus (für Demo & Debugging).
- [ ] Dokumentiere die Benutzung des Clients.

---

## 6. Dokumentation & Nachvollziehbarkeit

- [ ] Erstelle ein übersichtliches README mit:
  - [ ] Projektbeschreibung und Features
  - [ ] Anforderungen (Python-Version, Compiler, CMake, pip-Pakete)
  - [ ] Schritt-für-Schritt-Anleitung: Build, Server-Start, Client-Start
  - [ ] Hinweise zu möglichen Stolperstellen (z. B. PYTHONPATH)
  - [ ] Beispielausgaben (z. B. Server- und Client-Output)
  - [ ] API-Dokumentation (am besten auch über FastAPI-Autodoc erreichbar)
- [ ] Kommentiere den Code sinnvoll und nachvollziehbar.
- [ ] Stelle sicher, dass alle Module, Skripte und Build-Schritte klar nachvollziehbar sind.

---

## 7. Test & Abgabe

- [ ] Teste das gesamte System lokal durch:
  - [ ] Simuliere mehrere parallele Spiele und Spieler.
  - [ ] Prüfe, ob alle REST-Endpunkte wie beschrieben funktionieren.
  - [ ] Stelle sicher, dass Live-Updates funktionieren und der Spielverlauf korrekt abgebildet wird.
- [ ] Am Schluss: Teste den Ablauf auf einem „frischen“ System oder in einer neuen Umgebung.
- [ ] Kontrolliere, dass alles wie im README beschrieben läuft.

---

