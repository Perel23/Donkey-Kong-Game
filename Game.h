#pragma once

#include <vector>
#include <iomanip>
#include <thread>
#include <string>
#include "Ghost.h"
#include "Mario.h"
#include "Map.h"
#include "Barrel.h"
#include "Steps.h"
#include "Result.h"
#include <memory>


class Game
{
private:
    bool _isLoad;
    bool _isSave;
    bool _isSilent;

public:
    Game(bool isLoad, bool isSave, bool isSilent) : _isLoad(isLoad), _isSave(isSave), _isSilent(isSilent) {}

    // Core game functions
    void run();
    int startGame(std::vector<std::string>, int index);
    void pause();
    void drawMario(Mario& mario);

    // Game logic functions
    bool handleLifeLoss(int& currLives, Mario& mario, Map& gameBoard, static int& barrelCurr, static int& barrelCounter, bool& isMarioLocked, std::vector<std::unique_ptr<Ghost>>& ghosts, std::vector<Barrel>& barrels, int& score);
    void spawnBarrel(std::vector<Barrel>& barrels, int& barrelCurr, Map& gameBoard);
    void moveBarrels(std::vector<Barrel>& barrels, Mario& mario, bool isLoad, bool isSave, bool isSilent);
    void handleMarioLocked(char keyPressed, Mario& mario, bool& isMarioLocked);
    bool isMarioInLongAction(Mario& mario) const;
    bool isMarioInShortAction(Mario& mario) const;
    void toggleArrow(Map& gameBoard, const Point& point);
    void moveGhosts(std::vector<std::unique_ptr<Ghost>>& ghosts, bool isLoad, bool isSave, bool isSilent);
    void resetGhosts(std::vector<std::unique_ptr<Ghost>>& ghosts);
    void patishDestroy(std::vector<Barrel>& barrels, std::vector<std::unique_ptr<Ghost>>& ghosts, Mario& mario, char key, int& score, bool isSilent);

    // Utility functions
    std::vector<Point> defineFloorsToToggle(Map& map);
    void updateClock(std::chrono::steady_clock::time_point& startTime, int& elapsedSeconds, Map& gameBoard, int& score);
    void updateClock(const std::chrono::seconds& elapsedTime);
    bool getAllBoardFileNames(std::vector<std::string>& vec_to_fill);
    void handleErrors(int& flag);
    void noScreensMessage() const;
    void pressAnyKeyToMoveToNextStage() const;

    // Initialization functions
    Map initializeGameBoard(const std::string& fileName, bool isSilent);
    std::vector<Barrel> initializeBarrels(Map& gameBoard);
    std::vector<std::unique_ptr<Ghost>> initializeGhosts(Map& gameBoard);

    // Game state functions
    void pauseGame(Map& gameBoard, const int currLives);
    bool handlePatishInteraction(Mario& mario, bool& patishPicked, Map& gameBoard);
    void handleBarrelSpawning(std::vector<Barrel>& barrels, Map& gameBoard);
    void moveBarrelsAndGhosts(std::vector<Barrel>& barrels, std::vector<std::unique_ptr<Ghost>>& ghosts, Mario& mario, bool isLoad, bool isSave, bool isSilent);
    void toggleArrowsEvery13Iterations(Map& gameBoard, std::vector<Point>& togglePoints, size_t& iteration);
    void handleMarioMovement(Mario& mario, bool& isMarioLocked, char keyPressed, bool isSilent);
    void updateScore(Map& gameBoard, int score);

    // Virtual functions
    virtual void handleDieResult(std::pair<size_t, Results::ResultValue>& res,Results& results, const int& iteration, std::string fileName, bool& isResultGood) = 0;
    virtual void handlePaulineResult(std::pair<size_t, Results::ResultValue>& res, Results& results, const int& iteration, std::string fileName, bool& isResultGood) = 0;
    virtual char handleUserInput(Steps& steps, int iteration) = 0;
    virtual void handleStartOfGameLoop(Results& results, Steps& steps, std::string resultsFileName, std::string stepsFileName) = 0;
    virtual void handleEndOfGameLoop(Results& results, Steps& steps, std::string resultsFileName, std::string stepsFileName) = 0;
    virtual bool isReleventKeyPressed(const char& key) = 0;
    virtual void setRandomSeed(long& random_seed, Steps& steps) = 0;
    virtual void win() const = 0;
    virtual void lose() const = 0;
    virtual void loseALife() const;
    virtual void moveToNextStage(int stageIndex, bool isResultGood);
    virtual bool checkMissingFiles(const std::string& filename, const std::string& stepsFilename, const std::string& resultsFilename) = 0;


};
