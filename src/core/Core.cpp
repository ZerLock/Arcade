/*
** EPITECH PROJECT, 2023
** B-OOP-400-LYN-4-1-arcade-thomas.mazaud
** File description:
** Core
*/

#include "Core.hpp"

core::Core::Core(const std::string &firstLib) :
    _context(new arcade::Context(*this)),
    _libLoader(core::DLLoader(_getLibPath(firstLib))),
    _gameLoader(core::DLLoader("./lib/arcade_pacman.so")),
    _lib(nullptr),
    _game(nullptr),
    _menu(new game::Menu),
    _currentLibIndex(0),
    _currentGameIndex(0),
    _libs(),
    _games(),
    _inputsMap(),
    _isRunning(true),
    _isInMenu(true),
    _frameStart(std::chrono::steady_clock::now()),
    _username(),
    _scores(),
    _menuLibs(),
    _menuGames()
{
    // Ask to the user name in the console
    do {
        std::cout << "What is your name ?" << std::endl << "> ";
        std::getline(std::cin, _username);
    } while (_username.empty());

    // Get all libraries (graphicals and games)
    _getLibraries(firstLib);

    // get instance of arg library if all good
    if (_libLoader.call<arcade::LibType>("getType") == arcade::LibType::GRAPHICAL) {
        _lib = _libLoader.getInstance<render::IRenderer>();
    }

    if (!_lib) {
        throw core::Error("Argument library is not an Arcade graphic library");
    }
    if (_games.size() <= 0) {
        throw core::Error("There is not Arcade games in ./lib");
    }

    // Default inputs mapping
    _inputsMap = {
        {arcade::RawKey::K_M, arcade::Keymaps::NEXT_GRAPH},
        {arcade::RawKey::K_L, arcade::Keymaps::PREV_GRAPH},
        {arcade::RawKey::K_P, arcade::Keymaps::NEXT_GAME},
        {arcade::RawKey::K_O, arcade::Keymaps::PREV_GAME},
        {arcade::RawKey::K_BACKSPACE, arcade::Keymaps::QUIT},
        {arcade::RawKey::K_UP, arcade::Keymaps::UP},
        {arcade::RawKey::K_DOWN, arcade::Keymaps::DOWN},
        {arcade::RawKey::K_LEFT, arcade::Keymaps::LEFT},
        {arcade::RawKey::K_RIGHT, arcade::Keymaps::RIGHT},
        {arcade::RawKey::K_SPACE, arcade::Keymaps::PAUSE},
        {arcade::RawKey::K_ESCAPE, arcade::Keymaps::MENU},
        {arcade::RawKey::K_R, arcade::Keymaps::RESTART},
        {arcade::RawKey::K_ENTER, arcade::Keymaps::ENTER},
    };

    // Load score
    loadScore();

    // Setup menu
    _menu->setLibraries(_menuLibs, _currentLibIndex);
    _menu->setGames(_menuGames);
    _menu->setSelectedGame(_currentGameIndex);
    _menu->setSelectedLib(_currentLibIndex);
    _menu->setUsername(_username);
    _menu->setScores(_scores);
}

core::Core::~Core()
{
    delete _lib;
    if (!_isInMenu) {
        delete _game;
    }
    delete _menu;
    // Do not delete _context because of unique ptr
}

std::string core::Core::_getLibPath(const std::string &path)
{
    if ((path[0] != '.' || path[1] != '/') && path[0] != '/') {
        return "./" + path;
    }
    return path;
}

void core::Core::_getLibraries(const std::string &firstLib)
{
    const std::filesystem::path libsPath{"./lib"};

    for (auto const &dir_entry : std::filesystem::directory_iterator(libsPath)) {
        const std::string tmpPath = dir_entry.path().string();

        if (tmpPath.find(".so") != std::string::npos) {
            core::DLLoader tmpLoader = core::DLLoader(tmpPath);
            const auto tmpType = tmpLoader.call<arcade::LibType>("getType");

            if (tmpType == arcade::LibType::GRAPHICAL) {
                _libs.push_back(tmpPath);
                _menuLibs.push_back(tmpLoader.call<std::string>("getName"));
            } else if (tmpType == arcade::LibType::GAME) {
                _games.push_back(tmpPath);
                _menuGames.push_back(tmpLoader.call<std::string>("getName"));
            }
            if (tmpPath == _getLibPath(firstLib)) {
                _currentLibIndex = _libs.size() - 1;
            }
        }
    }

    bool found = false;
    for (auto tmp : _libs) {
        if (tmp == _getLibPath(firstLib)) {
            found = true;
        }
    }
    if (found == false) {
        _currentLibIndex = _libs.size();
        core::DLLoader tmpLoader = core::DLLoader(_getLibPath(firstLib));

        _libs.push_back(_getLibPath(firstLib));
        _menuLibs.push_back(tmpLoader.call<std::string>("getName"));
    }
}

render::IRenderer *&core::Core::getRenderer()
{
    return _lib;
}

void core::Core::saveScore(const std::size_t &score)
{
    auto gameName = _gameLoader.call<std::string>("getName");
    std::ofstream scoreFile ("./assets/score.txt", std::ios::app);

    if (scoreFile.is_open()) {
        scoreFile << gameName << ":" << _username << ":" << score << std::endl;
        scoreFile.close();
    }
}

void core::Core::loadScore()
{
    std::ifstream scoreFile ("./assets/score.txt");
    std::string line;

    if (scoreFile.is_open()) {
        while (std::getline(scoreFile, line)) {
            auto tabScore = _mySplit(line, ':');
            _scores[tabScore[0]].emplace_back(std::make_pair(tabScore[1], atoi(tabScore[2].c_str())));
        }
    }
}

std::map<arcade::RawKey, arcade::Keymaps> core::Core::getMapping() const
{
    return _inputsMap;
}

void core::Core::changeLib(std::size_t index)
{
    delete _lib;

    if (index >= _libs.size()) {
        return;
    }

    _currentLibIndex = index;
    _libLoader = core::DLLoader(_libs.at(_currentLibIndex));
    _lib = _libLoader.getInstance<render::IRenderer>();
    if (_game && _lib) {
        _lib->loadSpritesheets(_game->getSpritesheets());
    }
}

void core::Core::changeGame(std::size_t index)
{
    if (!_isInMenu) {
        delete _game;
    }
    _isInMenu = false;

    if (index >= _games.size()) {
        return;
    }

    _currentGameIndex = index;
    _gameLoader = core::DLLoader(_games.at(_currentGameIndex));
    _game = _gameLoader.getInstance<game::IGame>();
    if (_game && _lib) {
        _lib->loadSpritesheets(_game->getSpritesheets());
    }
}

std::chrono::duration<double> core::Core::_timer()
{
    auto now = std::chrono::steady_clock::now();
    std::chrono::duration<double> deltaTime = now - _frameStart;
    _frameStart = now;
    return deltaTime;
}

void core::Core::coreLoop()
{
    /*
     ** loop:
     **     - timer
     **     - events
     **     - update (IGame)
     **     - render (IRenderer)
     */
    while (_isRunning) {
        auto deltaTime = _timer();
        auto keys = _mapEvents(_lib->pollEvents());
        coreHandleInputs(keys);

        if (_isInMenu) {
            for (auto &key : keys) {
                _menu->handleInput(key);
            }
            _menu->compute(deltaTime, *_context);
            _menu->render(*_context);
        } else {
            for (auto &key : keys) {
                _game->handleInput(key);
            }
            _game->compute(deltaTime, *_context);
            _game->render(*_context);
        }
    }
}

void core::Core::_goToMenu()
{
    if (_isInMenu) {
        return;
    }

    _isInMenu = true;
    delete _game;
    _currentGameIndex = 0;
}

std::vector<arcade::KeyInput> core::Core::_mapEvents(std::vector<arcade::Event> keys)
{
    std::vector<arcade::KeyInput> inputs;

    for (auto &key : keys) {
        if (auto action = _inputsMap.find(key.key); action != _inputsMap.end()) {
            inputs.push_back({
                key,
                (*action).second,
            });
        }
    }
    return inputs;
}


void core::Core::coreHandleInputs(std::vector<arcade::KeyInput> keys)
{
    for (auto &key : keys) {
        switch (key.mapping) {
            case arcade::Keymaps::NONE:
                break;
            case arcade::Keymaps::QUIT:
                _isRunning = false;
                break;
            case arcade::Keymaps::NEXT_GRAPH:
                changeLib((_currentLibIndex + 1) % _libs.size());
                break;
            case arcade::Keymaps::PREV_GRAPH:
                if (_currentLibIndex == 0) {
                    _currentLibIndex = _libs.size();
                }
                changeLib((_currentLibIndex - 1) % _libs.size());
                break;
            case arcade::Keymaps::NEXT_GAME:
                changeGame((_currentGameIndex + 1) % _games.size());
                break;
            case arcade::Keymaps::PREV_GAME:
                if (_currentGameIndex == 0) {
                    _currentGameIndex = _games.size();
                }
                changeGame((_currentGameIndex - 1) % _games.size());
                break;
            case arcade::Keymaps::MENU:
                _goToMenu();
                break;
            case arcade::Keymaps::ENTER:
                if (!_isInMenu) {
                    break;
                }
                changeLib(_menu->getSelectedLib());
                changeGame(_menu->getSelectedGame());
                _menu->setSelectedGame(_menu->getSelectedGame());
                _menu->setSelectedLib(_menu->getSelectedLib());
                break;
            default:
                break;
        }
    }
}

std::vector<std::string> core::Core::_mySplit(const std::string &str, char delim) const
{
    std::istringstream ss (str);
    std::string token;
    std::vector<std::string> res = {};

    while (std::getline(ss, token, delim)) {
        res.push_back(token);
    }
    return res;
}