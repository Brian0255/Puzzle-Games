@echo off
SetLocal EnableDelayedExpansion
(set PATH=D:\Qt\6.2.0\msvc2019_64\bin;!PATH!)
if defined QT_PLUGIN_PATH (
    set QT_PLUGIN_PATH=D:\Qt\6.2.0\msvc2019_64\plugins;!QT_PLUGIN_PATH!
) else (
    set QT_PLUGIN_PATH=D:\Qt\6.2.0\msvc2019_64\plugins
)
%*
EndLocal
