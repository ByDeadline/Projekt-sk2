#pragma once

#include <vector>
#include <string>
#include <list>

#include "Player.h"

/// @brief Defines and manages a game
class Game
{
private:
    /// @brief A vector containing random texts that can be used in a game
    std::vector<std::string> randomTexts
    {
        "As collected deficient objection by it discovery sincerity curiosity. Quiet decay who round three world whole has mrs man. Built the china there tried jokes which gay why. Assure in adieus wicket it is. But spoke round point and one joy. Offending her moonlight men sweetness see unwilling. Often of it tears whole oh balls share an.",
        "Ladies others the six desire age. Bred am soon park past read by lain. As excuse eldest no moment. An delight beloved up garrets am cottage private. The far attachment discovered celebrated decisively surrounded for and. Sir new the particular frequently indulgence excellence how. Wishing an if he sixteen visited tedious subject it. Mind mrs yet did quit high even you went. Sex against the two however not nothing prudent colonel greater. Up husband removed parties staying he subject mr.",
        "Affronting discretion as do is announcing. Now months esteem oppose nearer enable too six. She numerous unlocked you perceive speedily. Affixed offence spirits or ye of offices between. Real on shot it were four an as. Absolute bachelor rendered six nay you juvenile. Vanity entire an chatty to.",
        "Am increasing at contrasted in favourable he considered astonished. As if made held in an shot. By it enough to valley desire do. Mrs chief great maids these which are ham match she. Abode to tried do thing maids. Doubtful disposed returned rejoiced to dashwood is so up.",
        "Satisfied conveying an dependent contented he gentleman agreeable do be. Warrant private blushes removed an in equally totally if. Delivered dejection necessary objection do mr prevailed. Mr feeling do chiefly cordial in do. Water timed folly right aware if oh truth. Imprudence attachment him his for sympathize. Large above be to means. Dashwood do provided stronger is. But discretion frequently sir the she instrument unaffected admiration everything.",
        "Remember outweigh do he desirous no cheerful. Do of doors water ye guest. We if prosperous comparison middletons at. Park we in lose like at no. An so to preferred convinced distrusts he determine. In musical me my placing clothes comfort pleased hearing. Any residence you satisfied and rapturous certainty two. Procured outweigh as outlived so so. On in bringing graceful proposal blessing of marriage outlived. Son rent face our loud near.",
        "Can curiosity may end shameless explained. True high on said mr on come. An do mr design at little myself wholly entire though. Attended of on stronger or mr pleasure. Rich four like real yet west get. Felicity in dwelling to drawings. His pleasure new steepest for reserved formerly disposed jennings.",
        "Had strictly mrs handsome mistaken cheerful. We it so if resolution invitation remarkably unpleasant conviction. As into ye then form. To easy five less if rose were. Now set offended own out required entirely. Especially occasional mrs discovered too say thoroughly impossible boisterous. My head when real no he high rich at with. After so power of young as. Bore year does has get long fat cold saw neat. Put boy carried chiefly shy general.",
        "Contented get distrusts certainty nay are frankness concealed ham. On unaffected resolution on considered of. No thought me husband or colonel forming effects. End sitting shewing who saw besides son musical adapted. Contrasted interested eat alteration pianoforte sympathize was. He families believed if no elegance interest surprise an. It abode wrong miles an so delay plate. She relation own put outlived may disposed."
    };

    /// @brief Index of the choosen text in randomTexts vector
    int chosenText = 0;

    /// @brief Number of words in the chosen text
    int wordCount = 0;

    /// @brief Flag telling if the game is finished
    bool finished = false;

    /// @brief Chooses a random text to be used as a text in this game
    void ChooseRandomText();

    /// @brief Calculate how many words the choosen text contains
    void CalculateWordCount();

public:
    /// @brief List of players in the game
    std::list<Player> players;

    /// @brief Gets the choosen text
    /// @return The choosen text
    std::string GetText() { return this->randomTexts[this->chosenText]; }

    /// @brief Gets the word count for the choosen text
    /// @return The word count for the choosen text
    int GetWordCount() { return this->wordCount; }

    /// @brief Gets a flag telling if the game is finished
    /// @return A flag telling if the game is finished
    bool IsFinished() { return this->finished; }

    /// @brief Sets the choosen player's progress to a choosen number
    /// @param userId User's unique id
    /// @param progress The progress to be set for the player
    void SetPlayerProgress(std::string userId, int progress);

    /// @brief Constructor
    /// @param players List of players to be in game
    Game(std::list<Player> players);

    /// @brief Destructor
    ~Game();
};