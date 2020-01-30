# ファイルの配置について

srcディレクトリ内に各re:viewファイルを配置していってください。  
各方の名前をprefixにつけてください。


# ローカルビルド環境構築

公開していただいているdockerイメージをそのまま利用します。  
ローカルにイメージをプルするだけです。

```
docker pull vvakame/review:latest
```

上記でうまく行かない場合 review バージョンが異なっています下記コマンドで 3.0 のイメージを利用します。

```
docker pull vvakame/review:3.0
```


# ローカルビルド方法

プロジェクトルートディレクトリで下記コマンド。  

```
docker run --rm -v `pwd`/src:/work vvakame/review /bin/sh -c "cd /work && review-pdfmaker config.yml"
```

エラーが出る場合下記コマンドで 3.0 のイメージでビルドします。

```
docker run --rm -v `pwd`/src:/work vvakame/review:3.0 /bin/sh -c "cd /work && review-pdfmaker config.yml"
```