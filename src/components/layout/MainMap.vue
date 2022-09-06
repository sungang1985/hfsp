<template>
    <div id="container">
        <div id="map"></div>
    </div>
</template>

<script>
import ExifReader from 'exifreader';

function openFile(event) {
    const input = event.target;

    const reader = new FileReader();
    reader.onload = function () {
        const result = reader.result;
        const tags = ExifReader.load(file);
        console.log(tags);

        Notiflix.Notify.info("The data has been loaded from the file");
    };
    reader.readAsText(input.files[0]);
}


export default {
    methods: {
        openFile(event) {
            const input = event.target;

            const reader = new FileReader();
            reader.onload = function () {
                const result = reader.result;
                const tags = ExifReader.load(file);
                console.log(tags);

                Notiflix.Notify.info("The data has been loaded from the file");
            };
            reader.readAsText(input.files[0]);
        },
        setupLeafletMap() {
            // config map
            let config = {
                minZoom: 7,
                maxZoom: 18,
                fullscreenControl: true,
            };
            // magnification with which the map will start
            const zoom = 18;
            // co-ordinates
            const lat = 52.22977;
            const lng = 21.01178;

            // calling map
            const map = L.map("map", config).setView([lat, lng], zoom);

            // Used to load and display tile layers on the map
            // Most tile servers require attribution, which you can set under `Layer`
            L.tileLayer("https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png", {
                attribution:
                    '&copy; <a href="https://www.openstreetmap.org/copyright">OpenStreetMap</a> contributors',
            }).addTo(map);



            Notiflix.Notify.init({
                width: "280px",
                position: "right-bottom",
                distance: "10px",
            });

            const customControl = L.Control.extend({
                // button position
                options: {
                    position: "topright",
                },

                // method
                onAdd: function () {
                    const array = [
                        {
                            title: "export features geojson",
                            html: "<svg class='icon-geojson'><use xlink:href='#icon-export'></use></svg>",
                            className: "export link-button leaflet-bar",
                        },
                        {
                            title: "save geojson",
                            html: "<svg class='icon-geojson'><use xlink:href='#icon-add'></use></svg>",
                            className: "save link-button leaflet-bar",
                        },
                        {
                            title: "remove geojson",
                            html: "<svg class='icon-geojson'><use xlink:href='#icon-remove'></use></svg>",
                            className: "remove link-button leaflet-bar",
                        },
                        {
                            title: "load gejson from file",
                            html: "<input type='file' id='geojson' class='geojson' /><label for='geojson'><svg class='icon-geojson'><use xlink:href='#icon-import'></use></svg></label>",
                            className: "load link-button leaflet-bar",
                        },
                    ];


                    const container = L.DomUtil.create(
                        "div",
                        "leaflet-control leaflet-action-button"
                    );

                    array.forEach((item) => {
                        const button = L.DomUtil.create("a");
                        button.href = "#";
                        button.setAttribute("role", "button");

                        button.title = item.title;
                        button.innerHTML = item.html;
                        button.className += item.className;

                        // add buttons to container;
                        container.appendChild(button);
                    });

                    return container;
                },
            });
            map.addControl(new customControl());

            const loadImgFiles = document.querySelector("#geojson");

            loadImgFiles.onchange = function (event) {
                const input = event.target;

                const reader = new FileReader();
                reader.onload = function () {
                    const result = reader.result;
                    const tags = ExifReader.load(result, { expanded: true });
                    console.log(tags);

                    Notiflix.Notify.info("The data has been loaded from the file");
                };
                reader.readAsArrayBuffer(input.files[0]);
            };

        },
    },
    mounted() {
        console.log(`the MainMap component is now mounted.`);
        this.setupLeafletMap();
    },
};
</script>
<style scoped>
#container {
    height: 85vh;
    display: flex;
    align-items: stretch;
}

#map {
    flex: 1;
}
</style>