// Fill out your copyright notice in the Description page of Project Settings.

#include "GVoiceClient.h"

UGVoiceClient* UGVoiceClient::GVoiceClient = nullptr;

UGVoiceClient::~UGVoiceClient()
{
	delete m_VoiceEngine;
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

