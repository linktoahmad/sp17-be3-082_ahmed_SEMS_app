import React, { Component } from "react";
import {StyleSheet} from "react-native";
import Speedometer from 'react-native-speedometer-chart';
import {Block, Text, Button, Linking} from "../components";
import { theme} from "../constants";

const volt_value =  Math.floor(Math.random() *100);

class Settings extends Component {

  dialCall = () => {
    Linking.openURL('tel:${091123456789}');
  };

  

  render() {
    

    return (
      <Block>
        <Block flex={false} row center space="between" style={styles.header}>
          <Text h1 bold>
            Usage Load
          </Text>
        </Block>
        <Block style = {{paddingHorizontal: theme.sizes.base * 2, paddingVertical:50 }}>
        <Speedometer 
        size={300}
        value={volt_value} 
        totalValue={100} 
        internalColor = '#4287f5'
        showLabels
        showIndicator />
          <Text center style={{ fontWeight: 'bold' , fontSize: 15 }}>Current Load</Text>
          <Text  center style={{ fontWeight: 'bold' , fontSize: 25 , color: '#4287f5' }}>{volt_value} amps</Text>
          <Text center>A ceiling fan consumes about 0.7 Amps this will give you an good idea about your usage load </Text>
          <Block middle flex={0.5} margin={[100, theme.sizes.padding * 2]}>
          <Text center style={{ color: '#bfbfbf' }}>If you are experiencing unreliable electricity contact authorities</Text>
          <Button RedGradient onPress={()=>this.dialCall}>
            <Text center bold white>
              Contact Authority
            </Text>
          </Button>
        </Block>
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
