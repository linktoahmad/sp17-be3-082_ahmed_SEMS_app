//https://github.com/christopherdro/react-native-html-to-pdf
// check this page out to learn print pdf
import React, { Component } from "react";
import {Block, Text, Button} from "../components";
import { theme} from "../constants";
import { Alert, PermissionsAndroid, Platform, StyleSheet, Image } from 'react-native';
 
import RNHTMLtoPDF from 'react-native-html-to-pdf';

class Settings extends Component {

  constructor(props) {
    super(props);
    this.state={
      filePath : ''
    }
  }
 
  requestRunTimePermission=()=> {
    var that = this;
    async function externalStoragePermission() {
    try {
      const granted = await PermissionsAndroid.request(
        PermissionsAndroid.PERMISSIONS.WRITE_EXTERNAL_STORAGE,
        {
          title: 'External Storage Write Permission',
          message:'App needs access to Storage data.',
        }
      );
      if (granted === PermissionsAndroid.RESULTS.GRANTED) {
        that.createPDF_File();
      } else {
        alert('WRITE_EXTERNAL_STORAGE permission denied');
      }
    } catch (err) {
      Alert.alert('Write permission err', err);
      console.warn(err);
    }
   }
 
    if (Platform.OS === 'android') {
      externalStoragePermission();
    } else {
      this.createPDF_File();
    }
  }
 
  async createPDF_File() {
    let options = {
      // HTML Content for PDF.
      // I am putting all the HTML code in Single line but if you want to use large HTML code then you can use + Symbol to add them.
      html:
        '<h1 style="text-align: center;"><strong>Welcome Guys</strong></h1><p style="text-align: center;">In This Tutorial we would learn about creating PDF File using HTML Text.</p><p style="text-align: center;"><strong>ReactNativeCode.com</strong></p>',
      // Setting UP File Name for PDF File.
      fileName: 'Sems-Report',
 
      //File directory in which the PDF File Will Store.
      directory: 'docs',
    };
 
    let file = await RNHTMLtoPDF.convert(options);
 
    console.log(file.filePath);
 
    Alert.alert(file.filePath);
 
    this.setState({filePath:file.filePath});
  }
  
  render() {
    

    return (
      <Block>
        <Block flex={false} row center space="between" style={styles.header}>
          <Text h1 bold>
            Save and Print
          </Text>
        </Block>
        <Block middle flex={0.5} margin={[100, theme.sizes.padding * 2]}>
          <Image source={require("../assets/images/bill.png")}/>    
        

          <Button gradient onPress={this.requestRunTimePermission}>
            <Text center bold white>
              Save 
            </Text>
          </Button>
 
          <Text gray center>File location is</Text>
          <Text center>{this.state.filePath}</Text>
              
          </Block>
      </Block>
    );
  }
}



export default Settings;

const styles = StyleSheet.create({
  header: {
    paddingHorizontal: theme.sizes.base * 2
  }
});
