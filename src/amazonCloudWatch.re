= Amazon CloudWatch
サービス:監視  対象:SRE、インフラ 区分:DevOps

//embed[latex]{
\begin{tcolorbox}[title=どんなサービス？,sharp corners]
Amazon CloudWatch は DevOps エンジニア、SRE、ITマネージャのために構築されたサービスモニタリングサービスです。
サービス監視項目として CPU、ディスク容量、メモリなどのリソースの使用率をログ、メトリクス、イベントという形式でデータを収集します。
収集できる監視項目は AWS のサービスによって異なり、AWSのほとんどすべてのサービスと CloudWatch が連携できます。
\end{tcolorbox}
//}

//image[illust][][scale=0.95]{
//}

//embed[latex]{
\clearpage
//}


#@# CloudWatch は単にサービスの監視するだけではなく、AWS リソースの最適化と運用パフォーマンスの向上に利用することも可能です。
#@# 例えば、ログとメトリクスから、アプリケーションの異常を検知し、アラームを設定、アクションを実行し管理者に通知などの自動化ができます。
#@# また、CloudWatch Events を利用することで、AWS Lambda や Amazon SNS など AWS の別のサービスへのワークフローのトリガーにすることもできます。


==[nonum] どんな時に使うの?
===[nonum] Amazon CloudWatch の3つの特徴

Amazon CloudWatch のが解決する課題は監視だけではありません。
AWS のクラウドを使っているからこそ出来る AWS サービスとの連携が一番の CloudWatch の特徴です。
ここでは 監視、運用、最適化の観点から 3 つの特徴を見てみましょう。

====[nonum]監視

CloudWatch はダッシュボードによってリアルタイムなメトリクスデータを表示できます。
最大15ヶ月分のメトリクスデータとともに監視項目を複合的に一画面で把握できるので、トラブルシューティングが迅速に行なえます。

====[nonum]運用

CloudWatch Logs は、アプリケーションのパフォーマンスを向上させるためのログの調査、分析、可視化が行なえます。  
運用上の問題点を迅速に解決するためのログ分析用クエリを実行することができます。

====[nonum]最適化

CloudWatch アラームは、しきい値や機械学習アルゴリズムによってサーバの異常を検知します。
アラームがトリガーされると、自動でインスタンスの停止や再起動、 EC2 AutoScaling の有効化が出来るため、
リソース配置の自動化が可能になります。

==[nonum] Amazon CloudWatch のコストは？
CloudWatch では従量課金制の料金体制になっています。
無料枠もあるので参考にしてみてください。


次の章からは、利用シーンに合わせた CloudWatch の活用事例をご紹介します。

//embed[latex]{
\clearpage
//}

==[nonum]CloudWatch の活用事例
===[nonum]ダッシュボードを活用した複合的なメトリクスの監視
ダッシュボードでは CloudWatch で収集した AWS サービスのメトリクスデータをグラフで表示できます。
グラフは、メトリクスデータの特性によって「テキストデータ」、「積み上げグラフ」、「折れ線グラフ」などの種類を選べます。
グラフのデータ軸は「分」、「時間」、「日」、「週」、「月」単位で表示できます。
サービスのリアルタイムな状況を表示し、アプリケーションに何が起こっているかを把握できます。
#@# また、週、月単位で負荷状況の推移をみて、リソースの最適化やサービスのボトルネックの解消にもこのダッシュボードのメトリクスデータが役に立ちます。
#@# 　さらに、1つのグラフに複数のメトリクスデータを重ねて表示できるため、関連するメトリクスを複合的に分析することで、迅速なトラブルシューティングの解決ができます。

//image[dashboard][][scale=0.65]{
//}

===[nonum]CloudWatch Logs Insights を利用した迅速なログ分析基盤
#@# 難しい文章
#@# CloudWatch Logs Insights は CluodWatch が収集する AWS サービスのログ（VPC Flow、Lambda、CloudTrail、RDS、S3、EC2など）
#@# や EC2 の Webサーバ、アプリケーションサーバログ（Apache、Nginx、php-fpmなど）を複合的に分析し、トラブルシューティングを迅速に行えるようにしたサービスです。
#@# 大量の複数のログを数秒で走査し、クエリを実行しグラフ化することができます。
#@# 　様々なフォーマットのログをまとめて走査できるため下記のようなアドホッククエリをサポートしています。

#@# 簡単な文
CloudWatch Logs Insights は CluodWatch が収集する AWS サービスのログや 
EC2 の Webサーバ、アプリケーションサーバログを複合的に分析し、
トラブルシューティングを迅速に行えるようにしたサービスです。
大量の複数のログ分析するためのクエリを実行しグラフ化することができます。

//image[cloudwatchInsight][][scale=0.70]{
//}


#@# 様々なフォーマットのログをまとめて走査できるため下記のようなアドホッククエリをサポートしています。

#@# ・コマンド 

#@# ・フィルタベースの条件指定  

#@# ・統計データの計算（パーセンタイルや時系列集計など）  

#@# ・希望するフィールドでのソート  

#@# ・正規表現

//embed[latex]{
\clearpage
//}

===[nonum] CloudWatch アラームによる EC2 インスタンスの自動停止、再起動
CloudWatch はメトリクスデータから任意のしきい値を設定しアラームアクションを設定することができます。
アラームアクションでは単純に SNS トピックスやメールなどと連携し、アラームを管理者に送信することができます。
監視対象が EC2 の場合はアラームを検知した後に、アラームアクションを使用して、EC2 インスタンスの停止、再起動、終了、または復旧を自動で行うこともできます。
サーバ内に再起動スクリプトなどを仕込まなくても AWS が裏側でインスタンスに対してアクションを実行してくれるので特別な仕組みの導入は入りません。

//image[illust][][scale=0.90]{
//}

