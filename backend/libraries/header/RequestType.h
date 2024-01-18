#pragma once

/// @brief Represents the type of a request a client can make
enum RequestType
{
    UserLogin,
    UserLogout,
    CreateLobby,
    ShowLobbies,
    JoinLobby,
    LeaveLobby,
    SetReady,
    GiveProgress,
    Alive,
    Unknown
};