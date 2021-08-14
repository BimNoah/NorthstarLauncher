#pragma once
#include "convar.h"
#include <WinSock2.h>

class RemoteServerInfo
{
public:
	char id[33]; // 32 bytes + nullterminator

	// server info
	char name[64];
	std::string description;
	char map[32];
	char playlist[16];

	int playerCount;
	int maxPlayers;

	// connection stuff
	bool requiresPassword;

public:
	RemoteServerInfo(const char* newId, const char* newName, const char* newDescription, const char* newMap, const char* newPlaylist, int newPlayerCount, int newMaxPlayers, bool newRequiresPassword);
};

struct RemoteServerConnectionInfo
{
public:
	char authToken[32];

	in_addr ip;
	int port;
};

class MasterServerManager
{
private:
	bool m_requestingServerList = false;
	bool m_authenticatingWithGameServer = false;
	bool m_savingPersistentData = false;

public:
	char m_ownServerId[33];

	bool m_scriptRequestingServerList = false;
	bool m_successfullyConnected = true;

	bool m_scriptAuthenticatingWithGameServer = false;
	bool m_successfullyAuthenticatedWithGameServer = false;

	bool m_hasPendingConnectionInfo = false;
	RemoteServerConnectionInfo m_pendingConnectionInfo;

	std::vector<RemoteServerInfo> m_remoteServers;

public:
	void ClearServerList();
	void RequestServerList();
	void AuthenticateWithOwnServer(char* uid, char* playerToken);
	void AuthenticateWithServer(char* uid, char* playerToken, char* serverId, char* password);
	void AddSelfToServerList(int port, int authPort, char* name, char* description, char* map, char* playlist, int maxPlayers, char* password);
	void UpdateServerMapAndPlaylist(char* map, char* playlist);
	void UpdateServerPlayerCount(int playerCount);
	void WritePlayerPersistentData(char* playerId, char* pdata, size_t pdataSize);
	void RemoveSelfFromServerList();
};

void InitialiseSharedMasterServer(HMODULE baseAddress);

extern MasterServerManager* g_MasterServerManager;
extern ConVar* Cvar_ns_masterserver_hostname;