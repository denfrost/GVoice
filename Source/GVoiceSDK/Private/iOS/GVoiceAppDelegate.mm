//
//  GVoiceAppDelegate.m
//  GCloudSample_Index
//
//  Created by vforkk on 9/11/2017.
//  Copyright © 2017 Epic Games, Inc. All rights reserved.
//

#ifdef __APPLE__
#ifndef __GVOICE_MAC__
#include "GVoiceAppDelegate.h"
#import <Foundation/Foundation.h>
#include "CoreDelegates.h"
#import "IOSAppDelegate.h"
#include <GVoice/GCloudVoice.h>


static void OnGVoiceAppDidEnterBackground()
{
    dispatch_async(dispatch_get_main_queue(), ^
                   {
                        gcloud_voice::GetVoiceEngine()->Pause();
                   });
                   
}

static void OnGVoiceAppWillEnterForeground()
{
    dispatch_async(dispatch_get_main_queue(), ^
                   {
                        gcloud_voice::GetVoiceEngine()->Resume();
                   });
                   
}

     
void GVoiceAppDelegate::Initialize()
{

    FCoreDelegates::ApplicationWillEnterBackgroundDelegate.AddStatic(&OnGVoiceAppDidEnterBackground);
    FCoreDelegates::ApplicationHasEnteredForegroundDelegate.AddStatic(&OnGVoiceAppWillEnterForeground);
    
    // Trigger GCloud SDK last now that everything is setup
    dispatch_sync(dispatch_get_main_queue(), ^
                   {
                       NSLog(@"initialize gvoice in main queue");                      
                   });
}

#endif
#endif


