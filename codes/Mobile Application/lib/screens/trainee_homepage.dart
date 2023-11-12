import 'package:flutter/material.dart';

class Trainee_homepage extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text('Home'),
      ),
      body: GridView.count(
        crossAxisCount: 2,
        children: [
          FeatureTile(
            icon: Icons.settings,
            title: 'Settings',
            onTap: () {
              // Add your logic for handling Settings feature here
            },
          ),
          FeatureTile(
            icon: Icons.person,
            title: 'Profile',
            onTap: () {
              // Add your logic for handling Profile feature here
            },
          ),
          FeatureTile(
            icon: Icons.play_circle_fill,
            title: 'Playback',
            onTap: () {
              // Add your logic for handling Playback feature here
            },
          ),
          FeatureTile(
            icon: Icons.feedback,
            title: 'Feedback',
            onTap: () {
              // Add your logic for handling Feedback feature here
            },
          ),
          FeatureTile(
            icon: Icons.bar_chart,
            title: 'Reports',
            onTap: () {
              // Add your logic for handling Reports feature here
            },
          ),
          FeatureTile(
            icon: Icons.mic,
            title: 'Recordings',
            onTap: () {
              // Add your logic for handling Recordings feature here
            },
          ),
        ],
      ),
    );
  }
}

class FeatureTile extends StatelessWidget {
  final IconData icon;
  final String title;
  final VoidCallback onTap;

  const FeatureTile({
    required this.icon,
    required this.title,
    required this.onTap,
  });

  @override
  Widget build(BuildContext context) {
    return InkWell(
      onTap: onTap,
      child: Card(
        child: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          children: [
            Icon(icon, size: 50, color: Colors.blue),
            SizedBox(height: 10),
            Text(
              title,
              style: TextStyle(fontSize: 18, fontWeight: FontWeight.bold),
            ),
          ],
        ),
      ),
    );
  }
}
