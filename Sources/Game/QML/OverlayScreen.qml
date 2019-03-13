import QtQuick 2.0
import QtGraphicalEffects 1.0
import QtQuick.Layouts 1.1

Item {
	id: screen

	property var source

	function toggle() {
		var isOn = state == "on";
		state = isOn? "off" : "on";
		return !isOn;
	}

	width: 200
	height: 200

	GaussianBlur {
		id: blur
		anchors.fill: parent
		radius: 8
		samples: 16
		source: screen.source
	}

	Colorize {
		id: colorize
		anchors.fill: parent
		source: blur
		hue: 0.8
		saturation: 0.5
		lightness: -0.5
	}

	MouseArea {
		anchors.fill: parent
		hoverEnabled: true
	}

	state: "on"
	states: [
		State {
			name: "on"
			PropertyChanges {
				target: blur
				radius: 8.0
			}
			PropertyChanges {
				target: screen
				opacity: 1.0
				enabled: true
			}
		},
		State {
			name: "off"
			PropertyChanges {
				target: blur
				radius: 0.0
			}
			PropertyChanges {
				target: screen
				opacity: 0.0
				enabled: false
			}
		}
	]

	transitions: [
		Transition {
			from: "on"; to: "off"
			reversible: true

			NumberAnimation {
				target: blur
				property: "radius"
				duration: 200
			}


			NumberAnimation {
				target: screen
				property: "opacity"
				duration: 200
			}
		}
	]
}
