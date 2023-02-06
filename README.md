Translated with www.DeepL.com/Translator (free version)  
Generated from the Readme_jp.md([日本語版](https://github.com/laycnc/UnrealExtenstionPluginsTemplates/blob/main/README_jp.md)) version

# UnrealExtensionPluginsTemplates

This plugin adds templates for new plugins.  
We have prepared a collection of code that is often written each time a plugin is created.  

![Additional Plug-in Templates](https://raw.githubusercontent.com/laycnc/UnrealExtenstionPluginsTemplates/readme-images/Images/AdditionalPlug-inTemplates.png "Templates that appear when the plugin is activated.")

# MinimalAsset

The `MinimalAsset` template creates the following elements.  

* Creation of a game runtime module
* Creation of an editor module
* Creation of an asset object (the thing with the plugin name)  
* Support creation from the content browser
  ![Create Asset](https://raw.githubusercontent.com/laycnc/UnrealExtenstionPluginsTemplates/readme-images/Images/CreateAsset.gif " Create dedicated asset from content browser")
* Creating `FAssetTypeActions`.  
  You can define asset colors, context menus, etc.  
* Create `Factory` asset  
  Create code to control the logic when creating an asset.

# MinimalAssetEditor

The `MinimalAssetEditor` template is created based on the `MinimalAsset` template with the following elements added.  

* `Commands` for the editor.
* Minimal code to create a dedicated editor that extends `FWorkflowCentricApplication`.  

![Minimal Asset Editor](https://raw.githubusercontent.com/laycnc/UnrealExtenstionPluginsTemplates/readme-images/Images/MinimalAssetEditor.png "Minimal Editor")


# MinimalGraph

The `MinimalGraph` template provides minimal graph creation functionality based on `BehaviorTree` related code.

* UndoRedo
* Basic context menu  
  ![context menu](https://raw.githubusercontent.com/laycnc/UnrealExtenstionPluginsTemplates/readme-images/Images/GraphNodeContextMenu.png "Basic Context Menu")
* Automatic placement of classes inheriting from `UPLUGIN_NAMENode` using `FGraphNodeClassHelper`.

![Graph editor sample](https://raw.githubusercontent.com/laycnc/UnrealExtenstionPluginsTemplates/readme-images/Images/MinimalGraphExample.gif)

# MinimalMovieScene

In the `MinimalMovieScene` template, the code for the minimum configuration of tracks + track editor used in the sequencer

* Sequencer tracks
* Track section

![CreateNewTrack](https://raw.githubusercontent.com/laycnc/UnrealExtenstionPluginsTemplates/readme-images/Images/CreateNewTrack.gif
 "Create New Track")

# MinimalSceneViewportEditor

The `MinimalSceneViewportEditor` template provides the minimal configuration for a viewport

* Viewport
* Viewport Settings

![MinimalSceneViewportEditor](https://raw.githubusercontent.com/laycnc/UnrealExtenstionPluginsTemplates/readme-images/Images/MinimalSceneViewportEditor.png "Minimal Scene Viewport Editor")