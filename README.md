# ファイルの配置について

srcディレクトリ内に各re:viewファイルを配置していってください。  
各方の名前をprefixにつけてください。


# ローカルビルド環境構築

公開していただいているdockerイメージをそのまま利用します。  
ローカルにイメージをプルするだけです。

```
docker pull vvakame/review:latest
```

# ローカルビルド方法

プロジェクトルートディレクトリで下記コマンド。  

```
docker run --rm -v `pwd`/src:/work vvakame/review /bin/sh -c "cd /work && review-pdfmaker config.yml"
```
