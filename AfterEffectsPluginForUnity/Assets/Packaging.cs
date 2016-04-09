#if UNITY_EDITOR
using System;
using System.Collections;
using UnityEngine;
using UnityEngine.Rendering;
using UnityEditor;


public class Packaging
{
    [MenuItem("Assets/UTJ/AfterEffectsPlugin/MakePackage")]
    public static void MakePackages()
    {
        string[] files = new string[]
        {
"Assets/UTJ",
        };
        AssetDatabase.ExportPackage(files, "AfterEffectsPlugin.unitypackage", ExportPackageOptions.Recurse);
    }

}
#endif
