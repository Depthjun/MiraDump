# :mag: MiraDump

Leave a **:star:star** if you find this helpful :)

**MiraDump** is a app that finds offsets of various games by pattern scanning the entire module according to the signature you specify. The biggest feature of this is this clean looks GUI which lets you work easily and Intuitively.

![app-image](https://user-images.githubusercontent.com/33578715/98183053-42907c80-1f42-11eb-893b-3f2a5dc7fc7b.png)

:warning:Do not use this to the game running with a modern anti-cheat. Or launch option `-insecure` will help you when you try this tool on the game under VAC protection.

# :fire: Get started

1. First of all, you **must** install following dependencies beforehand to build app properly.

- npm and node  -> [**Install from here**](https://www.npmjs.com/get-npm)

2. Once you install them, double click `MiraDump-build.cmd` in the project folder. This file will just run bunch of commands automatically for you to save your time. It's just text file after all, so you can take a look at what kinda commands would be executed.

3. If cmd file done its job without any errors, you will see `MiraDumpClient.exe`, `MiraDump.exe` as well as `config.toml` in the `dist/win-unpacked` folder in the project root.

4. Run `MiraDumpClient.exe` and GUI app will be launched. Refer to `How to use this app` for usage of this app.

# :sparkles: How to use this app

1. Specify the name of the target name in the first textarea and specify the directory you want result hpp file to be created.

![fundamental-info-image](https://user-images.githubusercontent.com/33578715/98184566-a9fbfb80-1f45-11eb-82fa-b133eab46ed0.png)

2. This is what they call profile. Specify following things here.
- **signature name** (anything)
- **actual signature**
- **module name** (including extention)
- **offset** (if you dont know what's offset and extra, read [this article](https://guidedhacking.com/resources/download-hazedumper-csgo-offset-dumper.24/))
- **extra**
- **x64relative** (This option is particularly for RIP-relative-addressing. If the target process is x86, just keep this untick)

![profiles-image](https://user-images.githubusercontent.com/33578715/98184731-0ced9280-1f46-11eb-9f5b-dd6721369a89.png)

3. Once you fill up the forms, click `Run MiraDump` button and you will see the result/error in the vast light blue field right below it:)

![run-btn-image](https://user-images.githubusercontent.com/33578715/98185201-1e836a00-1f47-11eb-9263-418babd401ef.png)

## Result would look like this

If you specify invalid informations in config.toml, the address will be 0x0 and corresponding error comment will be appear.
```hpp
namespace GameOffsetDumper {
    constexpr uintptr_t dwLocalPlayer = 0x6fd9d8 //client.dll
    constexpr uintptr_t InvalidModuleName = 0x0 //Invalid module name: client.dll
    constexpr uintptr_t BaseOfHandgun = 0x7b13ec //server.dll
    constexpr uintptr_t InvalidSignature = 0x0 //Invalid signature: 8Bxxxxx
}
```

# :notes: Background

The purpose of this project for me is reinventing the wheel and to use for my personal hacking activity in the future.
