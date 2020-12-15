import React from "react";
import { Image } from "react-native";
import { createAppContainer } from "react-navigation";
import { createStackNavigator } from "react-navigation-stack";

import Welcome from "../screens/Welcome";
import Login from "../screens/Login";
import UserLogin from "../screens/UserLogin";
import Forgot from "../screens/Forgot";
import addMeter from "../screens/addMeter";
import Explore from "../screens/Explore";
import Browse from "../screens/Browse";
import Settings from "../screens/Settings";
import Volts from "../screens/Volts";
import Amps from "../screens/Amps";
import Reports from "../screens/Reports";
import WeekReports from "../screens/WeekReports";
import MonthReports from "../screens/MonthReports";
import Limits from "../screens/Limits";
import Utilities from "../screens/Utilities";
import Printer from "../screens/Printer";

import { theme } from "../constants";

const screens = createStackNavigator(
  {
    Welcome,
    Login,
    UserLogin,
    Forgot,
    addMeter,
    Explore,
    Browse,
    Settings,
    Volts,
    Amps,
    Reports,
    WeekReports,
    MonthReports,
    Limits,
    Utilities,
    Printer
  },
  {
    defaultNavigationOptions: {
      headerStyle: {
        height: theme.sizes.base * 4,
        backgroundColor: theme.colors.white, // or 'white
        borderBottomColor: "transparent",
        elevation: 0 // for android
      },
      headerBackImage: <Image source={require("../assets/icons/back.png")} />,
      headerBackTitle: null,
      headerLeftContainerStyle: {
        alignItems: "center",
        marginLeft: theme.sizes.base * 2,
        paddingRight: theme.sizes.base
      },
      headerRightContainerStyle: {
        alignItems: "center",
        paddingRight: theme.sizes.base
      }
    }
  }
);

export default createAppContainer(screens);
