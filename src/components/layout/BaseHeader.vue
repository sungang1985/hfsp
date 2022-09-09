<template>
    <el-menu class="el-menu-demo" mode="horizontal" :ellipsis="false">
        <el-menu-item index="0">HFSP</el-menu-item>
        <el-sub-menu index="2">
            <template #title>文件</template>
            <el-menu-item index="2-1">
                <label id='loadImgFiles' for="inputTag" style="width: 100%;">打开文件<input id="inputTag"
                        type="file" /></label>
            </el-menu-item>
            <el-menu-item index="2-2" @click="saveFile">保存文件</el-menu-item>
        </el-sub-menu>
    </el-menu>
</template>

<script>
import ExifReader from 'exifreader';
import { useMapStore } from '../../stores/map'

export default {
    setup() {
        const mapStore = useMapStore()

        return {
            mapStore,
        }
    },
    methods: {
        saveFile() {
            console.log("save file!");
            console.log(this.mapStore.gps);
            L.marker([52.22977, 21.01178]).addTo(this.mapStore.map);
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
            //const map = L.map("map", config).setView([lat, lng], zoom);
            this.mapStore.init("map");
            const map = this.mapStore.map;
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

            const loadImgFiles = document.querySelector("#loadImgFiles");

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
        console.log(`the BaseHeader component is now mounted.`);
        //this.setupLeafletMap();
        const loadImgFiles = document.querySelector("#loadImgFiles");

        const mapStore = this.mapStore;

        loadImgFiles.onchange = function (event) {
            const input = event.target;

            const reader = new FileReader();
            reader.onload = function () {
                const result = reader.result;
                const tags = ExifReader.load(result, { expanded: true });
                console.log(tags);
                mapStore.setGPS(tags.gps);

                Notiflix.Notify.info("The data has been loaded from the file");
            };
            reader.readAsArrayBuffer(input.files[0]);
        };
    }
};
</script>
<style>
.el-header {
    margin: 0;
    padding: 0;
    height: 68px;
    /* background-color: aliceblue; */
    text-align: center;
    line-height: 68px;
}

input {
    display: none;
}
</style>