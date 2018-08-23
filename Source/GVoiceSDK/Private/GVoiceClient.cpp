// Fill out your copyright notice in the Description page of Project Settings.

#include "GVoiceClient.h"

UGVoiceClient* UGVoiceClient::GVoiceClient = nullptr;

UGVoiceClient::~UGVoiceClient()
{
	//delete m_VoiceEngine;
}

void UGVoiceClient::Tick(float DeltaTime)
{
	m_VoiceEngine->Poll();
}

bool UGVoiceClient::IsTickable() const
{
	return true;
}

TStatId UGVoiceClient::GetStatId() const
{
	return TStatId();
}

UGVoiceClient::UGVoiceClient(const FObjectInitializer& ObjectInitializer)
	: UObject{ ObjectInitializer }
	, m_VoiceEngine{ gcloud_voice::GetVoiceEngine() }
{
}

void UGVoiceClient::Initializer()
{
	if (!(GVoiceClient && GVoiceClient->IsValidLowLevel()))
	{
		GVoiceClient = NewObject<UGVoiceClient>();
		GVoiceClient->AddToRoot();
	}
}

UGVoiceClient* UGVoiceClient::GetVoiceClient()
{
	Initializer();
	return GVoiceClient;
}

int32 UGVoiceClient::SetAppInfo(const FString& appID, const FString& appKey, const FString& OpenID)
{
	if (nullptr == m_VoiceEngine) return -1;

	return m_VoiceEngine->SetAppInfo(TCHAR_TO_ANSI(*appID), TCHAR_TO_ANSI(*appKey), TCHAR_TO_ANSI(*OpenID));
}

int32 UGVoiceClient::InitVoiceEngine()
{
	return m_VoiceEngine->Init();
}

int32 UGVoiceClient::SetMode(EVoiceMode VoiceMode)
{
	return m_VoiceEngine->SetMode(static_cast<gcloud_voice::IGCloudVoiceEngine::GCloudVoiceMode>(VoiceMode));
}

int32 UGVoiceClient::OnPause()
{
	return m_VoiceEngine->Pause();
}

int32 UGVoiceClient::OnResume()
{
	return m_VoiceEngine->Resume();
}

int32 UGVoiceClient::JoinTeamRoom(const FString& RoomName, int32 msTimeout)
{
	return 0;
}

int32 UGVoiceClient::JoinNationalRoom(const FString& RoomName, EVoiceMemberRole MemberRole, int32 msTimeout)
{
	return 0;
}

