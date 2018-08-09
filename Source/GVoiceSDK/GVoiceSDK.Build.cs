// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System;
using System.IO;

public class GVoiceSDK : ModuleRules
{
#if WITH_FORWARDED_MODULE_RULES_CTOR
	public GVoiceSDK(ReadOnlyTargetRules Target) : base(Target)
#else
    public GVoiceSDK(TargetInfo Target)
#endif
	{
        string GVoiceLibPath = string.Empty;

        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
				"GVoiceSDK/Public",
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				"GVoiceSDK/Private",
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"GVoiceSDKLibrary",
				"Projects"
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);


        string PluginPath = Path.GetFullPath(Path.Combine(ModuleDirectory, "../../"));
        string GVoiceThirdPartyDir = Path.GetFullPath(Path.Combine(ModuleDirectory, "../ThirdParty/GVoiceSDKLibrary"));

        System.Console.WriteLine("-------------- PluginPath = " + PluginPath);

        if (Target.Platform == UnrealTargetPlatform.Android)
        {
            PrivateDependencyModuleNames.AddRange(new string[] { "Launch" });

            string aplPath = Path.Combine(PluginPath, "Source/GVoiceSDK/GVoiceSDK_APL.xml");
            System.Console.WriteLine("-------------- AplPath = " + aplPath);
            AdditionalPropertiesForReceipt.Add(new ReceiptProperty("AndroidPlugin", aplPath));
        }
        else if (Target.Platform == UnrealTargetPlatform.IOS )
        {

            PrivateIncludePaths.Add("GVoiceSDK/Private/IOS");
            PublicIncludePaths.AddRange(new string[] {"Runtime/ApplicationCore/Public/Apple", "Runtime/ApplicationCore/Public/IOS"});

            PrivateDependencyModuleNames.AddRange(
                new string[]{"ApplicationCore"
                // ... add private dependencies that you statically link with here ...
                }
                );
            /*
            BuildVersion Version;
            if(BuildVersion.TryRead(out Version))
            {
                System.Console.WriteLine("-------------- version = " + Version.MajorVersion +"."+Version.MinorVersion);
                if(Version.MajorVersion > 4 || (Version.MajorVersion == 4 && Version.MinorVersion >= 18))
                {
                    PrivateDependencyModuleNames.AddRange(
                    new string[]{"ApplicationCore"
                    // ... add private dependencies that you statically link with here ...
                    }
                    );
                }
            }
            */
        }
        else if (Target.Platform == UnrealTargetPlatform.Mac)
        {
            Definitions.Add("__GVOICE_MAC__");
        }

        if (Target.Platform == UnrealTargetPlatform.Win32 || Target.Platform == UnrealTargetPlatform.Win64)
        {
            PrivateIncludePaths.Add("GVoiceSDK/Public/GVoice/");

            string OSVersion = (Target.Platform == UnrealTargetPlatform.Win32) ? "x86" : "x64";
            GVoiceLibPath = Path.Combine(GVoiceThirdPartyDir, OSVersion, "lib");
            PublicLibraryPaths.Add(GVoiceLibPath);
            Console.WriteLine("GVoiceLibPath:" + GVoiceLibPath);

            PublicAdditionalLibraries.Add("GCloudVoice.lib");
            PublicDelayLoadDLLs.Add("GCloudVoice.dll");
            RuntimeDependencies.Add(new RuntimeDependency(Path.Combine(GVoiceLibPath, "GCloudVoice.dll")));


            string binariesDir = Path.Combine(PluginPath, "Binaries", Target.Platform.ToString());
            //string filename = Path.GetFileName(Filepath);
            string dllPath = Path.Combine(GVoiceLibPath, "GCloudVoice.dll");
            System.Console.WriteLine("src dll=" + dllPath + " dst dir=" + binariesDir);
            if (!Directory.Exists(binariesDir))
                Directory.CreateDirectory(binariesDir);
            try
            {
                File.Copy(dllPath, Path.Combine(binariesDir, "GCloudVoice.dll"), true);
            }
            catch (Exception e)
            {
                System.Console.WriteLine("copy dll exception,maybe have exists,err=", e.ToString());
            }
        }
        else if (Target.Platform == UnrealTargetPlatform.Android)
        {
            string ArchDir = "armeabi-v7a";
            //BASE
            string libDir = ("Android/GCloudVoice/libs");
            GVoiceLibPath = Path.Combine(Path.Combine(GVoiceThirdPartyDir, libDir), ArchDir);
            System.Console.WriteLine("--------------Android GCloudLibPath = " + GVoiceLibPath);
            PublicLibraryPaths.Add(GVoiceLibPath);
            AddGVoiceLib(Target, "GCloudVoice");
            //AddGCloudLib(Target, "TDataMaster");
            //AddGCloudLib(Target, "gcloud");

            //File srcFile = new File();

            // cz

        }
        else if (Target.Platform == UnrealTargetPlatform.Mac)
        {
            GVoiceLibPath = GVoiceThirdPartyDir;//
            string strLib = GVoiceLibPath+"/Mac/libGCloudVoice.a";
            PublicAdditionalLibraries.Add(strLib); 

        }
        else if (Target.Platform == UnrealTargetPlatform.IOS)
        {
            GVoiceLibPath = GVoiceThirdPartyDir;
            string strLib = GVoiceLibPath+"/iOS/libGCloudVoice.a";
            PublicAdditionalLibraries.Add(strLib);
            string strBundle = GVoiceLibPath+"/iOS/GCloudVoice.bundle";

            AdditionalBundleResources.Add(new UEBuildBundleResource("../ThirdParty/GVoiceSDKLibrary/iOS/GCloudVoice.bundle", bInShouldLog:false));

            System.Console.WriteLine("---framework path:"+Path.Combine(GVoiceLibPath, "VoiceFrameWork.embeddedframework.zip"));

            //PublicAdditionalFrameworks.Add(new UEBuildFramework("VoiceFWForBundle", "../ThirdParty/GVoiceSDKLibrary/iOS/VoiceFWForBundle.embeddedframework.zip", "iOS/GCloudVoice.bundle"));

            PublicAdditionalLibraries.AddRange(
            new string[] {
                "stdc++.6.0.9",
                //"libstdc++.6.0.9.tbd","libz.tbd","libc++.tbd","libz.1.1.3.tbd","libsqlite3.tbd","libxml2.tbd",
                //Path.Combine(GVoiceThirdPartyDir, "libAPMidasInterface.a")
            });

            
            // These are iOS system libraries that Facebook depends on (FBAudienceNetwork, FBNotifications)
            PublicFrameworks.AddRange(
            new string[] {
                "AVFoundation",
                "CoreTelephony",
                "Security",
                "SystemConfiguration",
                "AudioToolbox",
                "CoreAudio",
                "Foundation",
            });
            //AddGVoiceLib(Target, "libGCloudVoice.a");



            /*
            PublicAdditionalFrameworks.Add(new UEBuildFramework("ABase", Path.Combine(GCloudThirdPartyDir, "iOS/ABase.embeddedframework.zip")));
            */
        }

    }


#if WITH_FORWARDED_MODULE_RULES_CTOR
    private void AddGVoiceLib(ReadOnlyTargetRules Target, string in_libName)
#else
    private void AddGVoiceLib(TargetInfo Target, string in_libName)
#endif
    {
        if (Target.Platform == UnrealTargetPlatform.Android || Target.Platform == UnrealTargetPlatform.Linux || Target.Platform == UnrealTargetPlatform.IOS)
        {
            PublicAdditionalLibraries.Add(in_libName);
        }
        else if (Target.Platform == UnrealTargetPlatform.Mac)
        {
        }
        else
        {
            PublicAdditionalLibraries.Add(in_libName + ".lib");
        }
    }
}

