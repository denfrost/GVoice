// Fill out your copyright notice in the Description page of Project Settings.

#include "VoiceNotify.h"

UVoiceNotify::~UVoiceNotify()
{

}

void UVoiceNotify::OnJoinRoom(GCloudVoiceCompleteCode code, const char *roomName, int memberID)
{

}

void UVoiceNotify::OnStatusUpdate(GCloudVoiceCompleteCode status, const char *roomName, int memberID)
{

}

void UVoiceNotify::OnQuitRoom(GCloudVoiceCompleteCode code, const char *roomName)
{

}

void UVoiceNotify::OnMemberVoice(const unsigned int *members, int count)
{

}

void UVoiceNotify::OnMemberVoice(const char *roomName, unsigned int member, int status)
{

}

void UVoiceNotify::OnUploadFile(GCloudVoiceCompleteCode code, const char *filePath, const char *fileID)
{

}

void UVoiceNotify::OnDownloadFile(GCloudVoiceCompleteCode code, const char *filePath, const char *fileID)
{

}

void UVoiceNotify::OnPlayRecordedFile(GCloudVoiceCompleteCode code, const char *filePath)
{

}

void UVoiceNotify::OnApplyMessageKey(GCloudVoiceCompleteCode code)
{

}

void UVoiceNotify::OnSpeechToText(GCloudVoiceCompleteCode code, const char *fileID, const char *result)
{

}

void UVoiceNotify::OnRecording(const unsigned char* pAudioData, unsigned int nDataLength)
{

}

void UVoiceNotify::OnStreamSpeechToText(GCloudVoiceCompleteCode code, int error, const char *result, const char *voicePath)
{

}

void UVoiceNotify::OnRoleChanged(GCloudVoiceCompleteCode code, const char *roomName, int memberID, int role)
{

}

UVoiceNotify::UVoiceNotify(const FObjectInitializer& ObjectInitializer)
	:UObject{ ObjectInitializer }
{

}
