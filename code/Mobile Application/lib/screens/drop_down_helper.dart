import 'package:flutter/material.dart';
import 'esp.dart';
import 'rotation.dart';
class DropDownHelper extends StatefulWidget {
  const DropDownHelper({Key? key}) : super(key: key);
  @override
  State<DropDownHelper> createState() => _DropDownHelperState();
}
class _DropDownHelperState extends State<DropDownHelper> {
  List dropDownListData = [
    {"title": "Rotation", "value": "1"},
    {"title": "Acceleration", "value": "2"},
    {"title": "Velocity", "value": "3"},
  ];
  String defaultValue = "";
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        centerTitle: true,
        title: const Text("Comparison with expert surgeon"),
      ),
      body: Padding(
        padding: const EdgeInsets.all(10.0),
        child: ListView(
          children: [
            const SizedBox(height: 20),
            InputDecorator(
              decoration: InputDecoration(
                border: OutlineInputBorder(
                  borderRadius: BorderRadius.circular(15.0),
                ),
                contentPadding: const EdgeInsets.all(10),
              ),
              child: DropdownButtonHideUnderline(
                child: DropdownButton<String>(
                  isDense: true,
                  value: defaultValue,
                  isExpanded: true,
                  menuMaxHeight: 350,
                  items: [
                    const DropdownMenuItem(
                      child: Text("Select the technique"),
                      value: "",
                    ),
                    ...dropDownListData.map<DropdownMenuItem<String>>((data) {
                      return DropdownMenuItem(
                        child: Text(data['title']),
                        value: data['value'],
                      );
                    }).toList(),
                  ],
                  onChanged: (value) {
                    print("selected Value $value");
                    setState(() {
                      defaultValue = value!;
                    });
                  },
                ),
              ),
            ),
            const SizedBox(height: 20),
            ElevatedButton(
              onPressed: () {
                if (defaultValue == "2") {
                  print("Display chart for Acceleration");
                  Navigator.push(
                    context,
                    MaterialPageRoute(builder: (context) => MyApp()), // Navigate to the chart page
                  );// Navigate to the chart screen
                  // Add your navigation logic or state management here
                }else if(defaultValue == "1"){
                  print("Display chart for Rotation");
                  Navigator.push(
                    context,
                    MaterialPageRoute(builder: (context) => MyAppp()), // Navigate to the chart page
                  );// Navigate to the chart screen
                  // Add your navigation logic or state management here

                } 
                
                else {
                  print("Please select 'Force' to display the chart");
                }
              },
              child: const Text("Submit"),
            ),
          ],
        ),
      ),
    );
  }
}
