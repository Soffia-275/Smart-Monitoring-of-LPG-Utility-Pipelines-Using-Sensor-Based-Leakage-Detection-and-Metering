from flask import Flask, request, jsonify, render_template_string

app = Flask(__name__)

latest_data = {
    "gas_value": 0,
    "status": "SAFE",
    "latitude": 0,
    "longitude": 0
}

@app.route('/gasdata', methods=['POST'])
def receive_data():
    global latest_data
    data = request.get_json()

    latest_data["gas_value"] = data.get("gas_value")
    latest_data["status"] = data.get("status")
    latest_data["latitude"] = data.get("latitude")
    latest_data["longitude"] = data.get("longitude")

    print("Received:", latest_data)

    return jsonify({"message": "Data received"}), 200


@app.route('/')
def dashboard():
    html = f"""
    <html>
    <head>
        <title>Gas Monitoring Dashboard</title>
        <meta http-equiv="refresh" content="3">

        <link href="https://fonts.googleapis.com/css2?family=Poppins:wght@300;400;600&family=Montserrat:wght@500;700&display=swap" rel="stylesheet">

        <style>

        body {{
            margin:0;
            font-family:'Poppins', sans-serif;
            background:#0f172a;
            color:#e2e8f0;
        }}

        .header {{
            width:100%;
            padding:40px 0;
            text-align:center;
            font-family:'Montserrat', sans-serif;
            font-size:32px;
            font-weight:700;
            letter-spacing:1px;
            background:#020617;
            color:#22d3ee;
            border-bottom:2px solid #22d3ee;
        }}

        .container {{
            display:flex;
            justify-content:center;
            align-items:center;
            height:80vh;
        }}

        .dashboard {{
            width:850px;
            display:grid;
            grid-template-columns: repeat(2, 1fr);
            gap:30px;
        }}

        .card {{
            background:#111827;
            padding:35px;
            border-radius:12px;
            text-align:center;
            border:1px solid #1f2937;
            box-shadow:0 0 15px rgba(34,211,238,0.15);
            transition:0.3s;
        }}

        .card:hover {{
            transform:translateY(-5px);
            box-shadow:0 0 20px rgba(34,211,238,0.4);
        }}

        .label {{
            font-size:15px;
            margin-bottom:8px;
            color:#94a3b8;
        }}

        .value {{
            font-size:36px;
            font-weight:600;
        }}

        .status-safe {{
            color:#22c55e;
            font-weight:700;
        }}

        .status-leak {{
            color:#ef4444;
            font-weight:700;
        }}

        .map-container {{
            text-align:center;
            margin-top:35px;
        }}

        .map-btn {{
            padding:14px 28px;
            border-radius:8px;
            background:#06b6d4;
            color:#020617;
            font-size:16px;
            text-decoration:none;
            font-weight:600;
            transition:0.3s;
        }}

        .map-btn:hover {{
            background:#22d3ee;
        }}

        </style>

    </head>

    <body>

        <div class="header">
            Smart Gas Leak Monitoring Dashboard
        </div>

        <div class="container">

            <div>

                <div class="dashboard">

                    <div class="card">
                        <div class="label">Gas Sensor Value</div>
                        <div class="value">🧪 {latest_data["gas_value"]}</div>
                    </div>

                    <div class="card">
                        <div class="label">System Status</div>
                        <div class="value {'status-leak' if latest_data['status']=='LEAK' else 'status-safe'}">
                            ⚠ {latest_data["status"]}
                        </div>
                    </div>

                    <div class="card">
                        <div class="label">Latitude</div>
                        <div class="value">📍 {latest_data["latitude"]}</div>
                    </div>

                    <div class="card">
                        <div class="label">Longitude</div>
                        <div class="value">📍 {latest_data["longitude"]}</div>
                    </div>

                </div>

                <div class="map-container">
                    <a class="map-btn"
                    href="https://www.google.com/maps?q={latest_data['latitude']},{latest_data['longitude']}"
                    target="_blank">
                    🌍 Open Location in Google Maps
                    </a>
                </div>

            </div>

        </div>

    </body>
    </html>
    """

    return render_template_string(html)


if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)
