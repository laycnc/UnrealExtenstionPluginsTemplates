# UnrealExtenstionPluginsTemplates

新規プラグインのテンプレートを追加するプラグインです。  
プラグインを作成する際に、都度書くことが多いコードをまとめた物を用意しました。  

![Additional Plug-in Templates](https://raw.githubusercontent.com/laycnc/UnrealExtenstionPluginsTemplates/readme-images/Images/AdditionalPlug-inTemplates.png "プラグインを有効にすると表示されるテンプレート")

# MinimalAsset

`MinimalAsset`テンプレートでは、下記の要素が作成されます。  

* ゲームランタイムモジュールの作成
* エディターモジュールの作成
* アセットオブジェクト(プラグイン名の物)を作成  
* コンテンツブラウザからの作成をサポート
  ![Create Asset](https://raw.githubusercontent.com/laycnc/UnrealExtenstionPluginsTemplates/readme-images/Images/CreateAsset.gif "コンテンツブラウザから専用のアセット作成")
* `FAssetTypeActions`の作成  
  アセットのカラーや、コンテキストメニューなどの定義を行う事が出来ます。  
* アセット`Factory`の作成  
  アセットを作成時のロジックを制御するコードを作成します。

# MinimalAssetEditor

`MinimalAssetEditor`テンプレートでは、`MinimalAsset`テンプレートを元に以下の要素を追加した物が作成されます。  

* エディター向けの`Commands`
* `FWorkflowCentricApplication`を継承した専用のエディターを作成する為の最小限コード  

![Minimal Asset Editor](https://raw.githubusercontent.com/laycnc/UnrealExtenstionPluginsTemplates/readme-images/Images/MinimalAssetEditor.png "最小限のエディター")

# MinimalGraph

`MinimalGraph`テンプレートでは、`BehaviorTree`関連のコードを元に最小限のグラフ作成機能を用意しました。

* UndoRedo
* 基本的なコンテキストメニュー  
  ![コンテキストメニュー](https://raw.githubusercontent.com/laycnc/UnrealExtenstionPluginsTemplates/readme-images/Images/GraphNodeContextMenu.png "基本的なコンテキストメニュー")
* `FGraphNodeClassHelper`を使い`UPLUGIN_NAMENode`を継承したクラスの自動配置

![Graphエディターサンプル](https://raw.githubusercontent.com/laycnc/UnrealExtenstionPluginsTemplates/readme-images/Images/MinimalGraphExample.gif)

# MinimalMovieScene

`MinimalMovieScene`テンプレートでは、シーケンサーで使われるトラック＋トラックエディターの最小構成のコード

* シーケンサーのトラック
* トラックセクション

![CreateNewTrack](https://raw.githubusercontent.com/laycnc/UnrealExtenstionPluginsTemplates/readme-images/Images/CreateNewTrack.gif
 "Create New Track")

# MinimalSceneViewportEditor

MinimalSceneViewportEditor`テンプレートは、ビューポートの最小限の設定を提供します。

* ビューポート
* ビューポートの設定

![MinimalSceneViewportEditor](https://raw.githubusercontent.com/laycnc/UnrealExtenstionPluginsTemplates/readme-images/Images/MinimalSceneViewportEditor.png "Minimal Scene Viewport Editor")