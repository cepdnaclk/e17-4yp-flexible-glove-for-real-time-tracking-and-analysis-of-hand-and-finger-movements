import 'package:web_socket_channel/io.dart';
import 'package:flutter/material.dart';
import 'dart:async';
import 'dart:math';
import 'package:syncfusion_flutter_charts/charts.dart';

class MyAppp extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'WebSocket Client',
      theme: ThemeData(
        primarySwatch: Colors.blue,
      ),
      home: MyHomePage(),
    );
  }
}

class MyHomePage extends StatefulWidget {
  @override
  _MyHomePageState createState() => _MyHomePageState();
}

class _MyHomePageState extends State<MyHomePage> {
  final channel = IOWebSocketChannel.connect('ws://192.168.8.162');
  StreamSubscription? _subscription;
  List<double> chartData = []; // Store the data for the chart

  @override
  void initState() {
    super.initState();

    _subscription = channel.stream.listen((data) {
      List<dynamic> dataList = data.substring(2, data.length - 2).split('],[');
      for (var i = 1; i < dataList.length; i += 2) {
        List<dynamic> values = dataList[i].split(',');
        double x = double.parse(values[0]);
        double y = double.parse(values[1]);
        double z = double.parse(values[2]);
        double value = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));

        _updateDataSource(value);
      }
    });
  }

  void _updateDataSource(double value) {
    if (chartData.length >= 50) {
      chartData.removeAt(0); // Remove the oldest data point
    }
    setState(() {
      chartData.add(value);
    });
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text('Rotational Acceleration'),
      ),
      body: Center(
        child: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          children: <Widget>[
            SfCartesianChart(
              primaryXAxis: CategoryAxis(),
              series: <LineSeries<double, String>>[
                LineSeries<double, String>(
                  dataSource: chartData.map((value) => value).toList(),
                  xValueMapper: (value, _) => chartData.indexOf(value).toString(),
                  yValueMapper: (value, _) => value,
                ),
              ],
            ),
          ],
        ),
      ),
    );
  }

  @override
  void dispose() {
    _subscription?.cancel();
    channel.sink.close();
    super.dispose();
  }
}