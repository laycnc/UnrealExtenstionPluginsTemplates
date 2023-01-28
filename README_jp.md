# UnrealExtenstionPluginsTemplates

新規プラグインのテンプレートを追加するプラグインです。  
プラグインを作成する際に、都度書くことが多いコードをまとめた物を用意しました。  

![Additional Plug-in Templates](https://raw.githubusercontent.com/laycnc/UnrealExtenstionPluginsTemplates/readme-images/Images/AdditionalPlug-inTemplates.png "プラグインを有効にすると表示されるテンプレート")

# MinimalAsset

`MinimalAsset`テンプレートでは下記の要素が作成されます。  

* ゲームランタイムモジュールの作成
* エディターモジュールの作成
* アセットオブジェクト(プラグイン名の物)を作成  
* コンテンツブラウザからの作成をサポート
  ![Create Asset](https://raw.githubusercontent.com/laycnc/UnrealExtenstionPluginsTemplates/readme-images/Images/CreateAsset.gif "コンテンツブラウザから専用のアセット作成")
* `FAssetTypeActions`の作成  
  アセットのカラーや、コンテキストメニューなどの定義を行う事が出来ます。  
* アセット`Factory`の作成  
  アセットを作成時のロジックを制御するコードを作成します。

