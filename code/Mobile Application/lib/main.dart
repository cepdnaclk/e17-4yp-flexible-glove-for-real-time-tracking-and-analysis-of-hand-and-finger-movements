import 'package:flex_glove_application5/screens/login.dart';
import 'package:flex_glove_application5/screens/register.dart';
import 'package:flex_glove_application5/screens/trainee_homepage.dart';
import 'package:flutter/material.dart';
import 'package:firebase_core/firebase_core.dart';

void main() async {
  WidgetsFlutterBinding.ensureInitialized();
  await Firebase.initializeApp();
  runApp(MaterialApp(
    debugShowCheckedModeBanner: false,
    initialRoute: 'login',
    routes: {
      'login': (context) => Login(),
      'register': (context) => Register(),
      'Home_Trainee': (context) => Trainee_homepage()
    },
  ));
}
