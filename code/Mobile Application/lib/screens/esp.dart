import 'package:web_socket_channel/io.dart';
import 'package:flutter/material.dart';
import 'dart:async';
import 'dart:math';
import 'package:syncfusion_flutter_charts/charts.dart';

class MyApp extends StatelessWidget {
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
      for (var i = 0; i < dataList.length; i += 2) {
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
        title: Text('Acceleration graph'),
      ),
      body: Center(
        child: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          children: <Widget>[
            SfCartesianChart(
              primaryXAxis: CategoryAxis(),
              primaryYAxis: NumericAxis(minimum:5,maximum:15),
              series: <LineSeries<double, String>>[
                LineSeries<double, String>(
                  dataSource: chartData.map((value) => value).toList(),
                  xValueMapper: (value, _) => chartData.indexOf(value).toString(),
                  yValueMapper: (value, _) => value,
                ),
              ],
            ),
            SizedBox(height: 20),
            // Display the message based on the condition
            if (chartData.isNotEmpty)
              Text(
                getMessage(chartData.last), // Get message based on the last data point
                style: TextStyle(fontSize: 16),
            ),
          ],
        ),
      ),
    );
  }
  String getMessage(double value) {
    if (value > 11) {
      return 'Fast';
    } else if (value >= 10.1 && value <= 11) {
      return 'Normal';
    } else {
      return 'Slow';
    }
  }

  @override
  void dispose() {
    _subscription?.cancel();
    channel.sink.close();
    super.dispose();
  }
}