import 'package:flutter/material.dart';
import 'package:firebase_auth/firebase_auth.dart';
import 'package:fluttertoast/fluttertoast.dart';

class Login extends StatefulWidget {
  const Login({Key? key}) : super(key: key);

  @override
  State<Login> createState() => _LoginState();
}

class _LoginState extends State<Login> {
  TextEditingController _emailController = TextEditingController();
  TextEditingController _passwordController = TextEditingController();

  Future<void> _loginUser() async {
    String email = _emailController.text.trim();
    String password = _passwordController.text.trim();

    try {
      UserCredential userCredential =
          await FirebaseAuth.instance.signInWithEmailAndPassword(
        email: email,
        password: password,
      );

      // User successfully logged in
      print('User logged in: ${userCredential.user?.email}');
      // Show success toast
      Fluttertoast.showToast(
        msg: "Login successful!",
        toastLength: Toast.LENGTH_SHORT,
        gravity: ToastGravity.BOTTOM,
        timeInSecForIosWeb: 1,
        backgroundColor: Colors.green,
        textColor: Colors.black,
      );
    } catch (e) {
      // Handle login errors
      print('Error logging in: $e');
    }
  }

  @override
  Widget build(BuildContext context) {
    // Get the screen size and orientation using MediaQuery
    final mediaQuery = MediaQuery.of(context);
    final isPortrait = mediaQuery.orientation == Orientation.portrait;
    final screenHeight = mediaQuery.size.height;
    final screenWidth = mediaQuery.size.width;

    return Scaffold(
      appBar: null,
      body: Container(
        decoration: const BoxDecoration(
          image: DecorationImage(
            image: AssetImage('assets/login.png'),
            fit: BoxFit.cover,
          ),
        ),
        child: Scaffold(
          backgroundColor: Colors.transparent,
          body: Stack(
            children: [
              Container(),
              Container(
                padding: EdgeInsets.only(
                  left: isPortrait ? 35 : screenWidth * 0.2,
                  top: isPortrait ? 90 : screenHeight * 0.1,
                ),
                child: const Text(
                  'Welcome\nBack',
                  style: TextStyle(color: Colors.white, fontSize: 33),
                ),
              ),
              SingleChildScrollView(
                child: Container(
                  padding: EdgeInsets.only(
                    top: isPortrait ? screenHeight * 0.42 : screenHeight * 0.25,
                  ),
                  child: Column(
                    crossAxisAlignment: CrossAxisAlignment.start,
                    children: [
                      Container(
                        margin: EdgeInsets.only(
                          left: isPortrait ? 35 : screenWidth * 0.1,
                          right: isPortrait ? 35 : screenWidth * 0.1,
                        ),
                        child: Column(
                          children: [
                            TextField(
                              style: TextStyle(color: Colors.black),
                              controller: _emailController,
                              decoration: InputDecoration(
                                fillColor: Colors.grey.shade100,
                                filled: true,
                                hintText: "Email",
                                border: OutlineInputBorder(
                                  borderRadius: BorderRadius.circular(10),
                                ),
                              ),
                            ),
                            SizedBox(
                                height: isPortrait ? 30 : screenHeight * 0.02),
                            TextField(
                              style: TextStyle(),
                              controller: _passwordController,
                              obscureText: true,
                              decoration: InputDecoration(
                                fillColor: Colors.grey.shade100,
                                filled: true,
                                hintText: "Password",
                                border: OutlineInputBorder(
                                  borderRadius: BorderRadius.circular(10),
                                ),
                              ),
                            ),
                            SizedBox(
                                height: isPortrait ? 40 : screenHeight * 0.03),
                            Row(
                              mainAxisAlignment: MainAxisAlignment.spaceBetween,
                              children: [
                                Text(
                                  'Sign in',
                                  style: TextStyle(
                                    fontSize:
                                        isPortrait ? 27 : screenHeight * 0.04,
                                    fontWeight: FontWeight.w700,
                                  ),
                                ),
                                CircleAvatar(
                                  radius:
                                      isPortrait ? 30 : screenHeight * 0.035,
                                  backgroundColor:
                                      Color.fromARGB(255, 86, 157, 210),
                                  child: IconButton(
                                    color: Colors.white,
                                    onPressed:
                                        _loginUser, // Call the _loginUser function when the button is pressed
                                    icon: Icon(Icons.arrow_forward),
                                  ),
                                )
                              ],
                            ),
                            SizedBox(
                                height: isPortrait ? 40 : screenHeight * 0.03),
                            Row(
                              mainAxisAlignment: MainAxisAlignment.spaceBetween,
                              children: [
                                TextButton(
                                  onPressed: () {
                                    Navigator.pushNamed(context, 'register');
                                  },
                                  child: Text(
                                    'Sign Up',
                                    textAlign: TextAlign.left,
                                    style: TextStyle(
                                      decoration: TextDecoration.underline,
                                      color: Color(0xff4c505b),
                                      fontSize: isPortrait
                                          ? 18
                                          : screenHeight * 0.025,
                                    ),
                                  ),
                                ),
                                TextButton(
                                  onPressed: () {},
                                  child: Text(
                                    'Forgot Password',
                                    style: TextStyle(
                                      decoration: TextDecoration.underline,
                                      color: Color(0xff4c505b),
                                      fontSize: isPortrait
                                          ? 18
                                          : screenHeight * 0.025,
                                    ),
                                  ),
                                ),
                              ],
                            )
                          ],
                        ),
                      )
                    ],
                  ),
                ),
              ),
            ],
          ),
        ),
      ),
    );
  }
}
