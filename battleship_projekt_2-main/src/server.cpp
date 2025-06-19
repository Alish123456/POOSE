#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "game.hpp"

namespace py = pybind11;

PYBIND11_MODULE(battleship_py, m) {
    py::class_<battlespace::Game>(m, "Game")
        .def(py::init<int>(), py::arg("gameId"))
        .def("place_ship", &battlespace::Game::placeShip)
        .def("make_move", &battlespace::Game::makeMove)
        .def("get_state", &battlespace::Game::getState)
        .def("join", &battlespace::Game::join)
        .def("start_game", &battlespace::Game::startGame)
        .def("get_participants", &battlespace::Game::getParticipants)
        .def("get_next_player", &battlespace::Game::getNextPlayer);
}