// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GCloudVoice.h"
#include "GVoiceClient.generated.h"

/**
 * 
 */
UCLASS()
class GVOICESDK_API UGVoiceClient : public UObject
{
	GENERATED_BODY()

public:
	virtual ~UGVoiceClient();

	/**
	 * Get or New a voice client instance(if not exist), singleton object.
	 *
	 * @return UVoiceClient pointer
	 */
	UFUNCTION(BlueprintPure, Category = "GVoice")
		static UGVoiceClient* GetVoiceClient();
	
private:
	UGVoiceClient(const FObjectInitializer& ObjectInitializer);
	static void Initializer();

private:
	// The GVoiceClient instance pointer (singleton object)
	static UGVoiceClient* GVoiceClient;
	
	class gcloud_voice::IGCloudVoiceEngine* m_VoiceEngine;
};
