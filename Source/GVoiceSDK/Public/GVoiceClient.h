// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GCloudVoice.h"
#include "GVoiceClient.generated.h"

UENUM(BlueprintType)
enum class EVoiceMode : uint8
{
	/* realtime mode for TeamRoom or NationalRoom */
	RealTime = 0,
	/* voice message mode */
	Messages,
	/* speach to text mode */
	Translation,
	/* real-time speach to text mode */
	RSTT,
	/* high quality realtime voice, will cost more network traffic */
	HIGHQUALITY = 4,
};

/**
 * 
 */
UCLASS()
class GVOICESDK_API UGVoiceClient : public UObject, public FTickableGameObject
{
	GENERATED_BODY()

public:
	virtual ~UGVoiceClient();
	virtual void Tick(float DeltaTime) override;
	virtual bool IsTickable() const override;
	virtual TStatId GetStatId() const override;

	/**
	 * Get or New a voice client instance(if not exist), singleton object.
	 *
	 * @return UVoiceClient pointer
	 */
	UFUNCTION(BlueprintPure, Category = "GVoice")
		static UGVoiceClient* GetVoiceClient();

	/**
	 * Set VoiceEngine AppInfo.
	 *
	 * @param appID your game ID from gcloud.qq.com
	 * @param appKey your game key from gcloud.qq.com
	 * @param openID player's openID from QQ or Wechat. or a unit role ID.
	 * @return if m_voiceengine is nullptr return -1, if success return 0, failed return other errno @see GCloudVoiceErrno
	 * @see : GCloudVoiceErrno
	 */
	UFUNCTION(BlueprintCallable, Category = "GVoice")
		int32 SetAppInfo(const FString& appID, const FString& appKey, const FString& OpenID);

	/**
	  * Init the voice engine.
	  *
	  * @return if success return 0, failed return other errno @see GCloudVoiceErrno
	  * @see : GCloudVoiceErrno
	  */
	UFUNCTION(BlueprintCallable, Category = "GVoice")
		int32 InitVoiceEngine();

	/**
	 * Set the mode for engine.
	 *
	 * @param mode: mode to set
	 *              RealTime:    realtime mode for TeamRoom or NationalRoom
	 *              Messages:    voice message mode
	 *              Translation: speach to text mode
	 *				RSTT:		 real-time speach to text mode
	 *				HIGHQUALITY: high quality realtime voice, will cost more network traffic
	 * @return if success return 0, failed return other errno @see GCloudVoiceErrno
	 * @see : GCloudVoiceErrno
	 */
	UFUNCTION(BlueprintCallable, Category = "GVoice")
		int32 SetMode(EVoiceMode VoiceMode);

	/**
	 * The Application's Pause.
	 *
	 * When your app pause such as goto backend you should invoke this
	 * @return if success return 0, failed return other errno @see GCloudVoiceErrno
	 * @see : GCloudVoiceErrno
	 */
	UFUNCTION(BlueprintCallable, Category = "GVoice")
		int32 OnPause();

	/**
	* The Application's Resume.
	*
	* When your app reuse such as come back from  backend you should invoke this
	* @return if success return 0, failed return other errno @see GCloudVoiceErrno
	* @see : GCloudVoiceErrno
	*/
	UFUNCTION(BlueprintCallable, Category = "GVoice")
		int32 OnResume();
	
private:
	UGVoiceClient(const FObjectInitializer& ObjectInitializer);
	static void Initializer();

private:
	// The GVoiceClient instance pointer (singleton object)
	static UGVoiceClient* GVoiceClient;
	
	class gcloud_voice::IGCloudVoiceEngine* m_VoiceEngine;
};
