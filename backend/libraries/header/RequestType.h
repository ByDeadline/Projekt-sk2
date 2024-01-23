#pragma once

/// @brief Represents the type of a request a client can make
enum RequestType
{
    UserLogin,
    AdminLogin,
    UserLogout,
    RemoveUser,
    CreateLobby,
    ShowLobbies,
    JoinLobby,
    LeaveLobby,
    SetReady,
    GiveProgress,
    Alive,
    Unknown
};