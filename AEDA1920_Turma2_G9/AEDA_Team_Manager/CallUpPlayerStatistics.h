//
// Created by tiago on 22/10/2019.
//

#ifndef AEDA_TEAM_MANAGER_CALLUPGAMESTATISTICS_H
#define AEDA_TEAM_MANAGER_CALLUPGAMESTATISTICS_H
#include "Date.h"

class CallUpPlayerStatistics {
private:
    /**
     * Id of the player in question
     */
    int playerID;
    /**
     * Day that the player in question got in call up
     */
    Date begginingDate;
    /**
     * Day that the player in question left the call up
     */
    Date endDate;
public:
    /**
     * Construct object that represents peroid player was in call up
     * @param playerID - Id of the player in question
     * @param begginingDate - Day that the player in question got in call up
     * @param endDate - Day that the player in question left the call up
     */

    CallUpPlayerStatistics(int playerID, Date begginingDate, Date endDate);

    //GET METHODS
    /**
     * @return - playerID
     */
    int getPlayerID() const;
    /**
     * @return - Date player got in call up
     */
    Date getBegDate() const;
    /**
     * @return - Date player left call up
     */
    Date getEndDate() const;

    //SET METHODS
    /**
     * Sets player ID
     * @param playerID
     */
    void setPlayerID(const int &playerID);
    /**
     * Sets date player got in call up
     * @param begginingDate
     */
    void setBegDate(const Date &begginingDate);
    /**
     * Sets date player left call up
     * @param endDate
     */
    void setEndDate(const Date &endDate);
};


#endif //AEDA_TEAM_MANAGER_CALLUPGAMESTATISTICS_H
