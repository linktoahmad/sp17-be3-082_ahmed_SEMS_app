import React, { Component } from "react";
import {StyleSheet } from "react-native";
import ProgressCircle from 'react-native-progress-circle'

import {Block, Text, Switch } from "../components";
import { theme} from "../constants";
import NumericInput from 'react-native-numeric-input'

class Settings extends Component {
  state = {
    notifications: true,
    notifications2: true,
  };
  render() {
    

    return (
      <Block>
        <Block flex={false} style={styles.header}>
          <Text h1 bold>
            Set Limits
          </Text>
        </Block>

    <Block style={styles.header}>
        <Block row center space ="between" style={{flex:0.1}}>
              <Text gray>Activate Unit Limit</Text>
              <Switch
                value={this.state.notifications}
                onValueChange={value => this.setState({ notifications: value })}
              />
          </Block> 
          <Block row center space ="between" style={{flex:0.1}}>
              <Text gray>Set Unit Limit</Text>
              <NumericInput onChange={value => console.log(value)}
            minValue = {0}
            type = 'up-down'
            totalWidth={100} 
            totalHeight={40} 
            iconSize={10}
            rounded
            upDownButtonsBackgroundColor="#4287f5" />
          </Block> 
          <Block row center space ="between" style={{flex:0.1}}>
              <Text gray>Activate Load Limit</Text>
              <Switch
                value={this.state.notifications2}
                onValueChange={value => this.setState({ notifications2: value })}
              />
          </Block> 
          <Block row center space ="between" style={{flex:0.1}}>
              <Text gray>Set Load Limit</Text>
              <NumericInput onChange={value => console.log(value)}
            minValue = {0}
            type = 'up-down'
            totalWidth={100} 
            totalHeight={40} 
            iconSize={10}
            rounded
            upDownButtonsBackgroundColor="#4287f5" />
          </Block> 

          <Block style={[ {paddingTop:20 },{flexDirection:'row'}]}>
          <Block center>
            <ProgressCircle
                percent={35}
                radius={60}
                borderWidth={30}
                color="#4287f5"
                shadowColor="#999"
                bgColor="#fff">
              <Text style={{ fontSize: 15 }}>{'35%'}</Text>
            </ProgressCircle>
            <Text gray>Unit Consumed</Text>
          </Block>
          <Block center>
            <ProgressCircle
                percent={75}
                radius={60}
                borderWidth={30}
                color="#4287f5"
                shadowColor="#999"
                bgColor="#fff">
              <Text style={{ fontSize: 15 }}>{'75%'}</Text>
            </ProgressCircle>
            <Text gray>Load Consumed</Text>
          </Block>
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
