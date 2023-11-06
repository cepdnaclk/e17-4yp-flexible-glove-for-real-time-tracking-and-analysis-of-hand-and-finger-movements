import 'package:flutter/material.dart';
import 'package:web_socket_channel/io.dart';
import 'dart:async';

void main() {
  runApp(MyApp());
}

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
  final channel = IOWebSocketChannel.connect('ws://192.168.43.55');
  StreamSubscription? _subscription;
  List<String> messages = [];

  @override
  void initState() {
    super.initState();
    _subscription = channel.stream.listen((data) {
      setState(() {
        messages.add(data);
      });
    });
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text('WebSocket Client'),
      ),
      body: Center(
        child: ListView.builder(
          itemCount: messages.length,
          itemBuilder: (context, index) {
            return ListTile(
              title: Text(messages[index]),
            );
          },
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
